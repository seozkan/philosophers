/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:40:25 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 19:29:10 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clean_up(pthread_t *monitor, t_philo *philos)
{
	int	i;

	pthread_join(*monitor, NULL);
	i = 0;
	while (i < philos->info->philo_nbr)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philos->info->philo_nbr)
	{
		pthread_mutex_destroy(&philos[i].fork_r);
		pthread_mutex_destroy(&philos[i].status_mutex);
		pthread_mutex_destroy(&philos[i].eat_mutex);
		pthread_mutex_destroy(&philos[i].fed_mutex);
		i++;
	}
	pthread_mutex_destroy(&philos[0].info->print_mutex);
	free(philos);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	j = 1;
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
			{
				printf("Error: Parameters must be positive numbers only\n");
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

t_ms	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000 + time.tv_sec * 1000));
}

void	sensitive_usleep(t_ms time)
{
	t_ms	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
		usleep(200);
}
