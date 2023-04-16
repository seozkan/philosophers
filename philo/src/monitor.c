/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:40:35 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 17:19:42 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	pthread_mutex_lock(&philo->fed_mutex);
	if (philo->fed == false && get_time() - philo->info->start_time
		- philo->last_meal > philo->info->die_time)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		pthread_mutex_unlock(&philo->fed_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->fed_mutex);
	pthread_mutex_unlock(&philo->eat_mutex);
	return (false);
}

static bool	check_fed(t_philo *philo)
{
	pthread_mutex_lock(&philo->fed_mutex);
	if (philo->fed == true)
	{
		pthread_mutex_unlock(&philo->fed_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->fed_mutex);
	return (false);
}

static void	kill_all_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->philo_nbr)
	{
		pthread_mutex_lock(&philos[i].status_mutex);
		philos[i].status = false;
		pthread_mutex_unlock(&philos[i].status_mutex);
		i++;
	}
}

static void	end_dinner(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos->info->print_mutex);
	kill_all_philos(philos);
	printf("%lld %d %s\n", get_time() - philos[i].info->start_time,
		philos[i].num, DIE);
	pthread_mutex_unlock(&philos->info->print_mutex);
}

void	*monitor_routine(void *arg)
{
	t_philo			*philos;
	int				i;
	int				counter;

	philos = (t_philo *)arg;
	while (1)
	{
		usleep(50);
		i = 0;
		counter = 0;
		while (i < philos->info->philo_nbr)
		{
			if (check_death(&philos[i]))
			{
				end_dinner(philos, i);
				return (NULL);
			}
			if (check_fed(&philos[i++]))
				counter++;
		}
		if (counter == philos->info->philo_nbr)
			break ;
	}
	return (NULL);
}
