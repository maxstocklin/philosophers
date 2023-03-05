/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:43:57 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/05 19:29:51 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_exit(int elapsed_ms, int philow, int time_to_die, t_philo *philo)
{
	if ((elapsed_ms >= time_to_die))
	{
		pthread_mutex_lock(&philo->print_mutx[0]);
		if (*(philo->print) == 1)
			printf("%d %d died\n", elapsed_ms, philow + 1);
		*(philo->print) = 0;
		pthread_mutex_unlock(&philo->print_mutx[0]);

		//exit(0);
	}
}

void	*timer_thread(void *args)
{
	int					eaten;
	int					tmp_eat;
	struct timeval		st;
	struct timeval		ct;
	t_philo				*philo;
	int					elapsed_ms;

	gettimeofday(&st, NULL);
	eaten = 0;
	philo = (t_philo *) args;
	usleep( (philo->p_id * 100000));
	while (1)
	{
		pthread_mutex_lock(&philo->time_mutx[philo->p_id]);
		tmp_eat = philo->times_eaten;
		pthread_mutex_unlock(&philo->time_mutx[philo->p_id]);
		usleep(2000);
		if (tmp_eat > eaten)
		{
			eaten++;
			gettimeofday(&st, NULL);
		}
		gettimeofday(&ct, NULL);
		elapsed_ms = (ct.tv_sec - st.tv_sec) * MS + \
		(ct.tv_usec - st.tv_usec) / MS;
		pthread_mutex_lock(&philo->time_mutx[philo->p_id]);
		tmp_eat = philo->times_eaten;
		pthread_mutex_unlock(&philo->time_mutx[philo->p_id]);
		if (philo->eat_max != -1 && philo->eat_max <= tmp_eat)
			break ;
		ft_exit(elapsed_ms, philo->p_id, philo->time_to_die, philo);
		pthread_mutex_lock(&philo->print_mutx[0]);
		if (*(philo->print) == 0)
		{
			pthread_mutex_unlock(&philo->print_mutx[0]);
			break;
		}
		pthread_mutex_unlock(&philo->print_mutx[0]);

	}
	return (NULL);
}

void	ft_sleepwell(int time)
{
	struct timeval	st;
	struct timeval	ct;

	gettimeofday(&st, NULL);
	gettimeofday(&ct, NULL);
	while ((ct.tv_sec - st.tv_sec) * MS + (ct.tv_usec - st.tv_usec) / MS < time)
	{
		gettimeofday(&ct, NULL);
		usleep(100);
	}
}

void	ft_bon_app(int elapsed_ms, t_philo *philo, struct timeval st, \
struct timeval ct)
{
	pthread_mutex_lock(&philo->mutx[(philo->p_id + 1) % philo->p_nb]);
	gettimeofday(&ct, NULL);
	elapsed_ms = (ct.tv_sec - st.tv_sec) * MS + (ct.tv_usec - st.tv_usec) / MS;
	
	pthread_mutex_lock(&philo->print_mutx[0]);
	if (*(philo->print) == 1)
		printf("%d %d has taken a fork\n", elapsed_ms, philo->p_id + 1);
	pthread_mutex_unlock(&philo->print_mutx[0]);
	pthread_mutex_lock(&philo->mutx[(philo->p_id)]);
	gettimeofday(&ct, NULL);
	elapsed_ms = (ct.tv_sec - st.tv_sec) * MS + (ct.tv_usec - st.tv_usec) / MS;
	
	pthread_mutex_lock(&philo->print_mutx[0]);
	if (*(philo->print) == 1)
		printf("%d %d has taken a fork\n", elapsed_ms, philo->p_id + 1);
	pthread_mutex_unlock(&philo->print_mutx[0]);
	pthread_mutex_lock(&philo->time_mutx[philo->p_id]);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->time_mutx[philo->p_id]);
	
	pthread_mutex_lock(&philo->print_mutx[0]);
	if (*(philo->print) == 1)
		printf("%d %d is eating\n", elapsed_ms, philo->p_id + 1);
	pthread_mutex_unlock(&philo->print_mutx[0]);
	ft_sleepwell(philo->time_to_eat);
	pthread_mutex_unlock(&philo->mutx[philo->p_id]);
	pthread_mutex_unlock(&philo->mutx[(philo->p_id + 1) % philo->p_nb]);
	gettimeofday(&ct, NULL);
	elapsed_ms = (ct.tv_sec - st.tv_sec) * MS + (ct.tv_usec - st.tv_usec) / MS;
	
	
	pthread_mutex_lock(&philo->print_mutx[0]);
	if (*(philo->print) == 1)
		printf("%d %d is sleeping\n", elapsed_ms, philo->p_id + 1);
	pthread_mutex_unlock(&philo->print_mutx[0]);
	ft_sleepwell(philo->time_to_sleep);
	gettimeofday(&ct, NULL);
	elapsed_ms = (ct.tv_sec - st.tv_sec) * MS + (ct.tv_usec - st.tv_usec) / MS;
	usleep(50);
	
	
	pthread_mutex_lock(&philo->print_mutx[0]);
	if (*(philo->print) == 1)
		printf("%d %d is thinking\n", elapsed_ms, philo->p_id + 1);
	pthread_mutex_unlock(&philo->print_mutx[0]);
}

void	*philosophers_thread(void *args)
{
	int				elapsed_ms;
	t_philo			*philo;
	struct timeval	st;
	struct timeval	ct;

	philo = (t_philo *) args;
	gettimeofday(&st, NULL);
	if (philo->p_id % 2)
		usleep(15000 + (philo->p_id * 50));
	while (1)
	{
		elapsed_ms = (ct.tv_sec - st.tv_sec) * MS + \
		(ct.tv_usec - st.tv_usec) / MS;
		ft_bon_app(elapsed_ms, philo, st, ct);
		if (philo->eat_max != -1 && philo->eat_max <= philo->times_eaten)
			break ;
		pthread_mutex_lock(&philo->print_mutx[0]);
		if (*(philo->print) == 0)
		{
			pthread_mutex_unlock(&philo->print_mutx[0]);
			break;
		}
		pthread_mutex_unlock(&philo->print_mutx[0]);

	}
	return (NULL);
}
