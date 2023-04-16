/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:42:40 by seozkan           #+#    #+#             */
/*   Updated: 2023/04/16 17:22:01 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	create_philos(t_philo *philos)
{
	int			i;

	i = 0;
	while (i < philos->info->philo_nbr)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			philo_start(&philos[i]);
			return (0);
		}
		else if (philos[i].pid < 0)
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
		philos[i].num = i + 1;
		philos[i].fed = false;
		philos[i].info = info;
		philos[i].last_meal = 0;
		sem_unlink(EAT_SEM);
		philos[i].eat_sem = sem_open(EAT_SEM, O_CREAT, SEM_PERMS, 1);
		sem_unlink(FED_SEM);
		philos[i].fed_sem = sem_open(FED_SEM, O_CREAT, SEM_PERMS, 1);
		i++;
	}
}

int	init_info(t_info *info, int argc, char **argv)
{
	info->philo_nbr = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	info->meal_count = -1;
	if (argc == 6)
		info->meal_count = ft_atoi(argv[5]);
	if (errno == ERANGE)
		return (1);
	sem_unlink(FORKS_SEM);
	info->forks = sem_open(FORKS_SEM, O_CREAT, SEM_PERMS, info->philo_nbr);
	sem_unlink(PRINT_SEM);
	info->print_sem = sem_open(PRINT_SEM, O_CREAT, SEM_PERMS, 1);
	sem_unlink(STATUS_SEM);
	info->start_time = get_time();
	return (0);
}

static void	philo_alone(t_info *info)
{
	if (!info->meal_count)
		return ;
	printf("%d %d %s\n", 0, 1, FORK);
	sensitive_usleep(info->die_time);
	printf("%lld %d %s\n", info->die_time + 1, 1, DIE);
}

int	main(int argc, char **argv)
{
	t_info			info;
	t_philo			*philos;

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
	if (create_philos(philos))
		return (1);
	clean_up(philos);
	return (0);
}
