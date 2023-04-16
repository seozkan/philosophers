/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:05:29 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/16 16:25:11 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	clean_up(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].info->philo_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	while (--i >= 0)
	{
		sem_close(philos[i].eat_sem);
		sem_unlink(EAT_SEM);
		sem_close(philos[i].fed_sem);
		sem_unlink(FED_SEM);
	}
	sem_close(philos[0].info->forks);
	sem_unlink(FORKS_SEM);
	sem_close(philos[0].info->print_sem);
	sem_unlink(PRINT_SEM);
	free(philos);
}

int	ft_atoi(const char *str)
{
	int num;
	int i;

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
	int j;

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

void	sniper_usleep(t_ms time)
{
	t_ms	wake_up;

	wake_up = get_time() + time / 1000;
	while (get_time() < wake_up)
		usleep(200);
}
