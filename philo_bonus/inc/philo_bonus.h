/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:41:03 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 16:55:52 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/*INCLUDES*/
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

/*DEFINES*/
# define ACTION_COUNT 4
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define DIE "died"
# define FED_SEM "fed_sem"
# define EAT_SEM "eat_sem"
# define PRINT_SEM "print_sem"
# define FORKS_SEM "forks"
# define STATUS_SEM "status_sem"
# define SEM_PERMS 0600

/*TYPEDEFS*/
typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef void			(*t_func_action)(t_philo *philo);
typedef long long t_ms;

/* STRUCTS */
struct					s_philo
{
	t_info				*info;
	int					num;
	bool				fed;
	t_ms				last_meal;
	sem_t				*eat_sem;
	sem_t				*fed_sem;
	pid_t				pid;
};

struct					s_info
{
	int					philo_nbr;
	t_ms				die_time;
	t_ms				eat_time;
	t_ms				sleep_time;
	int					meal_count;
	t_ms				start_time;
	sem_t				*forks;
	sem_t				*print_sem;
	t_func_action		func_action[ACTION_COUNT];
};

/*PROTOTYPES*/
void					philo_take_forks(t_philo *philo);
void					philo_eat(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					philo_think(t_philo *philo);
void					print_action(t_philo *philo, char *str);
int						philo_start(t_philo *philo);
int						ft_atoi(const char *str);
t_ms					get_time(void);
int						check_args(int argc, char **argv);
int						init_info(t_info *info, int argc, char **argv);
void					sensitive_usleep(t_ms time);
void					clean_up(t_philo *philos);
void					*monitor_routine(void *arg);
#endif
