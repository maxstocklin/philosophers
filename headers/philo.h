/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:20:51 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/28 15:21:42 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h>
# include <string.h>
# include <sys/time.h>

# define MS 1000

typedef struct s_philo
{
	int				p_nb;
	int				p_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_max;
	int				times_eaten;
	pthread_mutex_t	*mutx;
	pthread_mutex_t	*time_mutx;
}					t_philo;

void	*philosophers_thread(void *args);
void	ft_bon_app(int elapsed_ms, t_philo *philo, struct timeval st, \
struct timeval ct);
void	*timer_thread(void *args);

int		atoi_check(const char *str, int i);
int		check_max_ints(char **av);
int		check_ints(char **av);
int		ft_check_error(char **av);

#endif
