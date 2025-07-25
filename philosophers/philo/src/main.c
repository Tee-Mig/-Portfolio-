/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:54:39 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/16 09:30:17 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_info	*info;
	t_philo	*philos;

	if ((ac == 5 || ac == 6) && parsing(ac, av))
	{
		info = malloc(sizeof(t_info));
		philos = malloc(sizeof(t_philo) * (ft_atoi(av[1])));
		if (error_malloc_struct(info, philos) == 0)
			return (1);
		if (fill_info(av, info, philos) == 0)
			return (0);
		philo_process(info, av, philos);
		free_all_end(info, philos);
	}
	else if (ac != 5 && ac != 6)
	{
		ft_putstr("Error: wrong number of argument\n");
		return (1);
	}
	return (0);
}

int	error_malloc_struct(t_info *info, t_philo *philos)
{
	if (!info || !philos)
	{
		if (info)
			free(info);
		if (philos)
			free(philos);
		printf("Error: malloc\n");
		return (0);
	}
	return (1);
}

void	free_all_end(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (++i < info->nb_philo)
		pthread_mutex_destroy(&info->forks[i]);
	pthread_mutex_destroy(&info->mutex_print);
	pthread_mutex_destroy(&info->check_dead);
	pthread_mutex_destroy(&info->check_dead_loop);
	pthread_mutex_destroy(&info->check_dead_process);
	pthread_mutex_destroy(&info->die);
	pthread_mutex_destroy(&info->check_nb_philo);
	free(info->forks);
	free(philos->philo);
	free(info);
	free(philos);
}
