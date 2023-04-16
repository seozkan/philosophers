/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:26:58 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 17:04:51 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*INCLUDES*/
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>  
# include <stdio.h>  
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h> 

/*DEFINES*/
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define DIE "died"

/*TYPEDEFS*/
typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef void			(*t_func_action)(t_philo *philo);
typedef long long t_ms;

/*STRUCTS*/
struct					s_philo
{
	t_info				*info;
	int					num;
	bool				fed;
	bool				status;
	t_ms				last_meal;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		status_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		fed_mutex;
	pthread_t			thread;
};

struct					s_info
{
	int					philo_nbr;
	t_ms				die_time;
	t_ms				eat_time;
	t_ms				sleep_time;
	int					meal_count;
	t_ms				start_time;
	pthread_mutex_t		print_mutex;
};

/* PROTOTYPES */
void					philo_take_forks(t_philo *philo);
void					philo_eat(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					philo_think(t_philo *philo);
void					print_action(t_philo *philo, char *str);
void					*philo_routine(void *arg);
int						check_args(int argc, char **argv);
void					init_info(t_info *info, int argc, char **argv);
int						ft_atoi(const char *str);
t_ms					get_time(void);
void					sensitive_usleep(t_ms time);
void					*monitor_routine(void *arg);
void					clean_up(pthread_t *waiter, t_philo *philos);
#endif
