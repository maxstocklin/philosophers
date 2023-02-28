/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:28:44 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/28 15:21:54 by mstockli         ###   ########.fr       */
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

void	ft_free(pthread_mutex_t	*mutx, pthread_t *thrds, t_philo *philo, int sz) // add mutx2!!
{
	int	i;

	i = -1;
	while (++i < sz)
	{
		pthread_join(thrds[i], NULL);
		pthread_mutex_destroy(&mutx[i]);
	}
	free(mutx);
	free(thrds);
	free(philo);
}

int	ft_philosophers(int ac, char **av)
{
	pthread_mutex_t	*mutx;
	pthread_mutex_t	*time_mutx;
	pthread_t		*threads;
	t_philo			*philo;
	int				i;

	mutx = malloc(atoi(av[1]) * sizeof(pthread_mutex_t));
	time_mutx = malloc(atoi(av[1]) * sizeof(pthread_mutex_t));
	threads = malloc(atoi(av[1]) * sizeof(pthread_t));
	philo = malloc(atoi(av[1]) * sizeof(t_philo));
	i = -1;
	while (++i < atoi(av[1]))
	{
		pthread_mutex_init(&mutx[i], NULL);
		philo[i].mutx = mutx;
		pthread_mutex_init(&time_mutx[i], NULL);
		philo[i].time_mutx = time_mutx;
		init_philo(philo, av, ac, i);
	}
	i = -1;
	while (++i < atoi(av[1]))
	{
		pthread_create(&threads[i], NULL, philosophers_thread, &philo[i]);
		pthread_create(&threads[i], NULL, timer_thread, &philo[i]);
	}
	ft_free(mutx, threads, philo, atoi(av[1])); // free time_mutx
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
