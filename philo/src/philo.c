/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:40:17 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 19:20:35 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->status_mutex);
	if (philo->is_alive == false)
	{
		pthread_mutex_unlock(&philo->status_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->status_mutex);
	return (false);
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (!check_death(philo))
		printf("%lld %d %s\n", get_time() - philo->info->start_time, philo->id,
			str);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

static void	set_fed(t_philo *philo)
{
	pthread_mutex_lock(&philo->fed_mutex);
	philo->fed = true;
	pthread_mutex_unlock(&philo->fed_mutex);
}

static void	make_routine(t_philo *philo)
{
	philo_take_forks(philo);
	philo_eat(philo);
	philo_sleep(philo);
	philo_think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		meals;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		sensitive_usleep(philo->info->eat_time / 2);
	meals = 0;
	while (!check_death(philo))
	{
		if (philo->info->meal_count != -1 && meals == philo->info->meal_count)
			break ;
		make_routine(philo);
		meals++;
	}
	set_fed(philo);
	return (NULL);
}
