/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:28:44 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/05 19:44:02 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_error(void)
{
	printf("Invalid parameters\n");
	exit(0);
}

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

void	ft_free(PM *mutx, PM *print_mutx, PM *time_mutx, t_philo *philo, int sz)
{
	int	i;

	i = -1;
	while (++i < sz)
	{
		pthread_mutex_destroy(&mutx[i]);
		pthread_mutex_destroy(&time_mutx[i]);
		pthread_mutex_destroy(&print_mutx[i]);
	}
	free(print_mutx);
	free(time_mutx);
	free(mutx);
	free(philo);
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

void	ft_create_threads(t_struct data, t_philo *philo, int i, char **av)
{
	while (++i < atoi(av[1]))
	{
		pthread_create(&data.threads[i], NULL, philosophers_thread, &philo[i]);
		pthread_create(&data.timer_threads[i], NULL, timer_thread, &philo[i]);
	}
	ft_join(atoi(av[1]), data.threads, data.timer_threads);
	ft_free(data.time_mutx, data.print_mutx, data.mutx, philo, atoi(av[1]));
}

int	ft_philosophers(int ac, char **av)
{
	t_struct	data;
	t_philo		*philo;
	int			i;
	int			print;

	malloc_mtx_thrds(&data, av);
	philo = malloc(atoi(av[1]) * sizeof(t_philo));
	if (!philo)
		exit (0);
	i = -1;
	print = 1;
	while (++i < atoi(av[1]))
	{
		pthread_mutex_init(&data.mutx[i], NULL);
		philo[i].mutx = data.mutx;
		pthread_mutex_init(&data.time_mutx[i], NULL);
		philo[i].time_mutx = data.time_mutx;
		pthread_mutex_init(&data.print_mutx[i], NULL);
		philo[i].print_mutx = data.print_mutx;
		init_philo(philo, av, ac, i);
		philo[i].print = &print;
	}
	ft_create_threads(data, philo, -1, av);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (check_ints(av) == 1 || check_max_ints(av) == 1)
			ft_error();
		ft_philosophers(ac, av);
	}
	else
		ft_error();
	return (0);
}
