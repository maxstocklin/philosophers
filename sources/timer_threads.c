/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:38:13 by max               #+#    #+#             */
/*   Updated: 2023/03/05 20:38:36 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_exit(t_time timer, int philow, int time_to_die, t_philo *philo)
{
	int	t_ms;

	if (philo->times_eaten > 1)
		t_ms = timer.total_ms;
	else
		t_ms = timer.elapsed_ms;
	if ((timer.elapsed_ms >= time_to_die))
	{
		pthread_mutex_lock(&philo->print_mutx[0]);
		if (*(philo->print) == 1)
			printf("%d %d died\n", t_ms, philow + 1);
		*(philo->print) = 0;
		pthread_mutex_unlock(&philo->print_mutx[0]);
	}
}

void	ft_mutex_eaten(t_philo *philo, t_time *timer)
{
	pthread_mutex_lock(&philo->time_mutx[philo->p_id]);
	timer->tmp_eat = philo->times_eaten;
	pthread_mutex_unlock(&philo->time_mutx[philo->p_id]);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutx[0]);
	if (*(philo->print) == 0)
	{
		pthread_mutex_unlock(&philo->print_mutx[0]);
		return (1);
	}
	pthread_mutex_unlock(&philo->print_mutx[0]);
	return (0);
}

void	ft_reset_time(t_time *timer)
{
	if (timer->tmp_eat > timer->eaten)
	{
		timer->eaten++;
		gettimeofday(&timer->st, NULL);
	}
	gettimeofday(&timer->ct, NULL);
}

void	*timer_thread(void *args)
{
	t_philo			*philo;
	t_time			timer;

	gettimeofday(&timer.st, NULL);
	timer.started_ms = (timer.st.tv_sec * MS) + (timer.st.tv_usec / MS);
	timer.eaten = 0;
	philo = (t_philo *) args;
	while (1)
	{
		ft_mutex_eaten(philo, &timer);
		usleep(500);
		ft_reset_time(&timer);
		timer.elapsed_ms = (timer.ct.tv_sec - timer.st.tv_sec) * MS + \
		(timer.ct.tv_usec - timer.st.tv_usec) / MS;
		timer.total_ms = ((timer.ct.tv_sec * MS) + \
		(timer.ct.tv_usec / MS)) - timer.started_ms;
		ft_mutex_eaten(philo, &timer);
		if (philo->eat_max != -1 && philo->eat_max <= timer.tmp_eat)
			break ;
		ft_exit(timer, philo->p_id, philo->time_to_die, philo);
		if (check_dead(philo) == 1)
			break ;
	}
	return (NULL);
}
