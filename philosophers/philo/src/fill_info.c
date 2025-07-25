/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:58:28 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/16 11:40:17 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	fill_info(char **av, t_info *info, t_philo *philos)
{
	info->forks = malloc(sizeof(pthread_mutex_t) * (atoi(av[1])));
	philos->philo = malloc(sizeof(pthread_t) * (atoi(av[1])));
	if (error_malloc_info(info, philos) == 0)
		return (0);
	info->nb_philo = atoi(av[1]);
	info->time_to_die = atoi(av[2]);
	info->time_to_eat = atoi(av[3]);
	info->time_to_sleep = atoi(av[4]);
	if (av[5] != NULL)
		info->must_eat = atoi(av[5]);
	else
		info->must_eat = -1;
	info->end = 0;
	info->begin_time = get_time();
	info->state_fork_one = 0;
	fill_info2(info, philos);
	pthread_mutex_init(&info->mutex_print, NULL);
	pthread_mutex_init(&info->check_dead, NULL);
	pthread_mutex_init(&info->check_dead_loop, NULL);
	pthread_mutex_init(&info->check_dead_process, NULL);
	pthread_mutex_init(&info->die, NULL);
	pthread_mutex_init(&info->check_nb_philo, NULL);
	return (1);
}

int	error_malloc_info(t_info *info, t_philo *philos)
{
	if (!info->forks || !philos->philo)
	{
		if (info->forks)
			free(info->forks);
		if (philos->philo)
			free(philos->philo);
		free(info);
		free(philos);
		printf("Error: malloc\n");
		return (0);
	}
	return (1);
}

void	fill_info2(t_info *info, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		if (i == 0)
			philos[i].right_fork = info->nb_philo - 1;
		else
			philos[i].right_fork = i - 1;
		philos[i].left_fork = i;
		philos[i].nb_eat = 0;
		philos[i].id_philo = i + 1;
		philos[i].time_last_eat = get_time();
		philos[i].finished_eat = 0;
		philos[i].info = info;
		pthread_mutex_init(&info->forks[i], NULL);
	}
}
