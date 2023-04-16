/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:50:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/16 15:44:19 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_take_forks(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_r);
		print_action(philo, FORK);
		pthread_mutex_lock(philo->fork_l);
		print_action(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		print_action(philo, FORK);
		pthread_mutex_lock(&philo->fork_r);
		print_action(philo, FORK);
	}
}

void	philo_eat(t_philo *philo)
{
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_meal = get_time() - philo->info->start_time;
	pthread_mutex_unlock(&philo->eat_mutex);
	sniper_usleep(philo->info->eat_time);
	pthread_mutex_unlock(&philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	sniper_usleep(philo->info->sleep_time);
}

void	philo_think(t_philo *philo)
{
	print_action(philo, THINK);
	if (philo->info->philo_count % 2 != 0)
		sniper_usleep(philo->info->eat_time / 2);
}
