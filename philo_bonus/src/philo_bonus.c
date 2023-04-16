/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:42:49 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 21:02:39 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	print_action(t_philo *philo, char *str)
{
	sem_wait(philo->info->print_sem);
	if (check_death_all() == true)
	{
		sem_post(philo->info->print_sem);
		return ;
	}
	printf("%s%lld %d %s\n%s", CYAN, get_time() - philo->info->start_time,
		philo->id, str, END);
	sem_post(philo->info->print_sem);
}

static void	make_routine(t_philo *philo)
{
	philo_take_forks(philo);
	philo_eat(philo);
	philo_sleep(philo);
	philo_think(philo);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		meals;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		sensitive_usleep(philo->info->eat_time / 2);
	meals = 0;
	while (!check_death_all())
	{
		if (philo->info->meal_count != -1 && meals == philo->info->meal_count)
			break ;
		make_routine(philo);
		meals++;
	}
	sem_wait(philo->fed_sem);
	philo->fed = true;
	sem_post(philo->fed_sem);
	return (NULL);
}

int	philo_start(t_philo *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &monitor_routine, philo))
		return (1);
	philo_routine(philo);
	pthread_join(monitor, NULL);
	return (0);
}
