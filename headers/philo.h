/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:20:51 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/21 15:03:30 by mstockli         ###   ########.fr       */
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
	pthread_mutex_t	*print_mutx;
	pthread_mutex_t	*time_mutx;
	int				*print;
}					t_philo;

typedef struct s_struct
{
	pthread_mutex_t	*mutx;
	pthread_mutex_t	*time_mutx;
	pthread_mutex_t	*print_mutx;
	pthread_t		*threads;
	pthread_t		*timer_threads;

}					t_struct;

typedef struct s_time
{
	int				elapsed_ms;
	int				started_ms;
	int				total_ms;
	int				eaten;
	int				tmp_eat;
	struct timeval	st;
	struct timeval	ct;
}					t_time;

void	*philosophers_thread(void *args);
void	ft_bon_app(int elapsed_ms, t_philo *philo, struct timeval st, \
struct timeval ct);

void	eat_sleep_rinse_repeat(int elapsed_ms, t_philo *philo, \
struct timeval st, struct timeval ct);

void	ft_exit(t_time timer, int philow, int time_to_die, t_philo *philo);
void	ft_mutex_eaten(t_philo *philo, t_time *timer);
int		check_dead(t_philo *philo);
void	ft_reset_time(t_time *timer);
void	*timer_thread(void *args);

int		atoi_check(const char *str, int i);
int		check_max_ints(char **av);
int		check_ints(char **av);
int		ft_check_error(char **av);
int		ft_error(void);

void	init_philo(t_philo *philo, char **av, int ac, int i);
void	ft_join(int sz, pthread_t *threads, pthread_t *timer_threads);
int		malloc_mtx_thrds(t_struct *data, char **av);

int		ft_atoi(const char *s);

#endif
