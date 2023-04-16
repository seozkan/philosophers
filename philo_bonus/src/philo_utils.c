/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:50:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/16 15:49:44 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_think(t_philo *philo)
{
	print_action(philo, THINK);
}

void	philo_eat(t_philo *philo)
{
	print_action(philo, EAT);
	sem_wait(philo->eat_sem);
	philo->last_meal = get_time() - philo->info->start_time;
	sem_post(philo->eat_sem);
	sniper_usleep(philo->info->eat_time);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_action(philo, FORK);
	sem_wait(philo->info->forks);
	print_action(philo, FORK);
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	sniper_usleep(philo->info->sleep_time);
}
