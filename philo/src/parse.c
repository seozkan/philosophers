/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:05:29 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/16 15:45:36 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

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

void	init_info(t_info *info, int argc, char **argv)
{
	info->philo_count = ft_atoi(argv[1]);
	info->starve_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]) * 1000;
	info->sleep_time = ft_atoi(argv[4]) * 1000;
	info->meal_count = -1;
	if (argc == 6)
		info->meal_count = ft_atoi(argv[5]);
	pthread_mutex_init(&info->print_mutex, NULL);
	info->func_action[0] = &philo_take_forks;
	info->func_action[1] = &philo_eat;
	info->func_action[2] = &philo_sleep;
	info->func_action[3] = &philo_think;
	info->start_time = get_time();
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