/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:40:06 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 19:17:34 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	create_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->philo_nbr)
	{
		if (pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	init_philos(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info->philo_nbr)
	{
		philos[i].id = i + 1;
		philos[i].is_alive = true;
		philos[i].fed = false;
		philos[i].info = info;
		philos[i].last_meal = info->start_time;
		pthread_mutex_init(&philos[i].fork_r, NULL);
		pthread_mutex_init(&philos[i].status_mutex, NULL);
		pthread_mutex_init(&philos[i].eat_mutex, NULL);
		pthread_mutex_init(&philos[i].fed_mutex, NULL);
		philos[i].fork_l = &philos[(i + 1) % info->philo_nbr].fork_r;
		i++;
	}
}

static void	init_info(t_info *info, int argc, char **argv)
{
	info->philo_nbr = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	info->meal_count = -1;
	if (argc == 6)
		info->meal_count = ft_atoi(argv[5]);
	pthread_mutex_init(&info->print_mutex, NULL);
	info->start_time = get_time();
}

static void	philo_alone(t_info *info)
{
	printf("%d %d %s\n", 0, 1, FORK);
	sensitive_usleep(info->die_time);
	printf("%lld %d %s\n", info->die_time + 1, 1, DIE);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philos;
	pthread_t	monitor;

	if (check_args(argc, argv))
		return (1);
	init_info(&info, argc, argv);
	if (info.philo_nbr == 1)
	{
		philo_alone(&info);
		return (0);
	}
	philos = malloc(sizeof(t_philo) * info.philo_nbr);
	if (!philos)
		return (1);
	init_philos(&info, philos);
	if (pthread_create(&monitor, NULL, &monitor_routine, philos))
		return (1);
	if (create_philos(philos))
		return (1);
	clean_up(&monitor, philos);
	return (0);
}
