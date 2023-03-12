/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:46:57 by max               #+#    #+#             */
/*   Updated: 2023/03/05 19:48:04 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	init_philo(t_philo *philo, char **av, int ac, int i)
{
	philo[i].p_nb = atoi(av[1]);
	philo[i].p_id = i;
	philo[i].time_to_die = atoi(av[2]);
	philo[i].time_to_eat = atoi(av[3]);
	philo[i].time_to_sleep = atoi(av[4]);
	philo[i].times_eaten = 0;
	philo[i].eat_max = -1;
	if (ac == 6)
		philo[i].eat_max = atoi(av[5]);
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

void	malloc_mtx_thrds(t_struct *data, char **av)
{
	data->mutx = malloc(atoi(av[1]) * sizeof(pthread_mutex_t));
	data->time_mutx = malloc(atoi(av[1]) * sizeof(pthread_mutex_t));
	data->print_mutx = malloc(atoi(av[1]) * sizeof(pthread_mutex_t));
	data->threads = malloc(atoi(av[1]) * sizeof(pthread_t));
	data->timer_threads = malloc(atoi(av[1]) * sizeof(pthread_t));
	if (!data->timer_threads || !data->threads || !data->print_mutx || \
	!data->time_mutx || !data->mutx)
		exit (0);
}
