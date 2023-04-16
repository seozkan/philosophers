/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:42:49 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 17:27:22 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static bool	check_death(void)
{
	sem_t	*status;

	status = sem_open(STATUS_SEM, 0);
	if (status == SEM_FAILED)
		return (false);
	sem_close(status);
	return (true);
}

void	print_action(t_philo *philo, char *str)
{
	sem_wait(philo->info->print_sem);
	if (check_death() == true)
	{
		sem_post(philo->info->print_sem);
		return ;
	}
	printf("%lld %d %s\n", get_time() - philo->info->start_time, philo->num,
		str);
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
	if (philo->num % 2 == 0)
		sensitive_usleep(philo->info->eat_time / 2);
	meals = 0;
	while (!check_death())
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
	pthread_t	waitress;

	if (pthread_create(&waitress, NULL, &monitor_routine, philo))
		return (1);
	philo_routine(philo);
	pthread_join(waitress, NULL);
	return (0);
}
