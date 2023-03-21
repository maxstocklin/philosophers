/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:43:57 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/21 14:48:41 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

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
	gettimeofday(&ct, NULL);
	elapsed_ms = (ct.tv_sec - st.tv_sec) * MS + (ct.tv_usec - st.tv_usec) / MS;
	pthread_mutex_lock(&philo->print_mutx[0]);
	if (*(philo->print) == 1)
		printf("%d %d has taken a fork\n", elapsed_ms, philo->p_id + 1);
	pthread_mutex_unlock(&philo->print_mutx[0]);
	if (philo->p_nb < 2)
		return ;
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
}

void	eat_sleep_rinse_repeat(int elapsed_ms, t_philo *philo, \
struct timeval st, struct timeval ct)
{
	pthread_mutex_lock(&philo->mutx[(philo->p_id + 1) % philo->p_nb]);
	ft_bon_app(elapsed_ms, philo, st, ct);
	if (philo->p_nb < 2)
		return ;
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
		eat_sleep_rinse_repeat(elapsed_ms, philo, st, ct);
		if (philo->eat_max != -1 && philo->eat_max <= philo->times_eaten)
			break ;
		if (check_dead(philo) == 1 || philo->p_nb < 2)
			break ;
	}
	return (NULL);
}
