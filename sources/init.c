/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:46:57 by max               #+#    #+#             */
/*   Updated: 2023/03/21 15:03:53 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	init_philo(t_philo *philo, char **av, int ac, int i)
{
	philo[i].p_nb = ft_atoi(av[1]);
	philo[i].p_id = i;
	philo[i].time_to_die = ft_atoi(av[2]);
	philo[i].time_to_eat = ft_atoi(av[3]);
	philo[i].time_to_sleep = ft_atoi(av[4]);
	philo[i].times_eaten = 0;
	philo[i].eat_max = -1;
	if (ac == 6)
		philo[i].eat_max = ft_atoi(av[5]);
}

void	ft_join(int sz, pthread_t *threads, pthread_t *timer_threads)
{
	int	i;

	i = -1;
	while (++i < sz)
	{
		pthread_join(threads[i], NULL);
		pthread_join(timer_threads[i], NULL);
	}
	free(threads);
	free(timer_threads);
}

int	malloc_mtx_thrds(t_struct *data, char **av)
{
	data->mutx = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	data->time_mutx = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	data->print_mutx = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	data->threads = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	data->timer_threads = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	if (!data->timer_threads || !data->threads || !data->print_mutx || \
	!data->time_mutx || !data->mutx)
		return (-1);
	return (0);
}
