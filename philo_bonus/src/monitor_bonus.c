/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:43:01 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 21:01:15 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

bool	check_death_all(void)
{
	sem_t	*status;

	status = sem_open(STATUS_SEM, 0);
	if (status == SEM_FAILED)
		return (false);
	sem_close(status);
	return (true);
}

static bool	check_death(t_philo *philo)
{
	sem_wait(philo->eat_sem);
	sem_wait(philo->fed_sem);
	if (philo->fed == false && get_time() - philo->info->start_time
		- philo->last_meal > philo->info->die_time)
	{
		sem_post(philo->eat_sem);
		sem_post(philo->fed_sem);
		return (true);
	}
	sem_post(philo->eat_sem);
	sem_post(philo->fed_sem);
	return (false);
}

static void	kill_all_philos(void)
{
	sem_unlink(STATUS_SEM);
	sem_open(STATUS_SEM, O_CREAT, SEM_PERMS, 0);
}

static void	end_dinner(t_philo *philo)
{
	printf("%lld %d %s\n", get_time() - philo->info->start_time,
		philo->id, DIE);
	kill_all_philos();
	sem_post(philo->info->print_sem);
}

void	*monitor_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(50);
		sem_wait(philo->info->print_sem);
		sem_wait(philo->fed_sem);
		if (check_death_all() == true || philo->fed == true)
		{
			sem_post(philo->fed_sem);
			sem_post(philo->info->print_sem);
			return (NULL);
		}
		sem_post(philo->fed_sem);
		if (check_death(philo))
		{
			end_dinner(philo);
			return (NULL);
		}
		sem_post(philo->info->print_sem);
	}
	return (NULL);
}
