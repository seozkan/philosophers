/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:41:03 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 21:01:39 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/*INCLUDES*/
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

/*DEFINES*/
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

# define CYAN "\033[33;36;1m"
# define END "\033[0;0m"

/*TYPEDEFS*/
typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef long long		t_ms;

/* STRUCTS */
struct					s_philo
{
	t_info				*info;
	int					id;
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
};

/*PROTOTYPES*/
bool					check_death_all(void);
void					*monitor_routine(void *arg);
void					philo_think(t_philo *philo);
void					philo_eat(t_philo *philo);
void					philo_take_forks(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					print_action(t_philo *philo, char *str);
int						philo_start(t_philo *philo);
void					clean_up(t_philo *philos);
int						ft_atoi(const char *str);
int						check_args(int argc, char **argv);
t_ms					get_time(void);
void					sensitive_usleep(t_ms time);

#endif
