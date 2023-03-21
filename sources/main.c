/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:28:44 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/21 15:03:44 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_free(t_struct data, t_philo *philo, int sz)
{
	int	i;

	i = -1;
	while (++i < sz)
	{
		pthread_mutex_destroy(&data.mutx[i]);
		pthread_mutex_destroy(&data.time_mutx[i]);
		pthread_mutex_destroy(&data.print_mutx[i]);
	}
	free(data.print_mutx);
	free(data.time_mutx);
	free(data.mutx);
	free(philo);
}

void	ft_create_threads(t_struct data, t_philo *philo, int i, char **av)
{
	while (++i < ft_atoi(av[1]))
	{
		pthread_create(&data.threads[i], NULL, philosophers_thread, &philo[i]);
		pthread_create(&data.timer_threads[i], NULL, timer_thread, &philo[i]);
	}
	ft_join(ft_atoi(av[1]), data.threads, data.timer_threads);
	ft_free(data, philo, ft_atoi(av[1]));
}

int	ft_philosophers(int ac, char **av)
{
	t_struct	data;
	t_philo		*philo;
	int			i;
	int			print;

	if (malloc_mtx_thrds(&data, av) == -1)
		return (-1);
	philo = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	if (!philo)
		return (-1);
	i = -1;
	print = 1;
	while (++i < ft_atoi(av[1]))
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
			return (ft_error());
		if (ft_philosophers(ac, av) == -1)
			return (0);
	}
	else
		ft_error();
	return (0);
}
