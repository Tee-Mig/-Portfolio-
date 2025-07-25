/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:50:48 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/16 11:38:38 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_dead_philo(t_info *info, t_philo *philos)
{
	int	i;

	while (!info->end)
	{
		usleep(1000);
		i = 0;
		pthread_mutex_lock(&philos->info->check_nb_philo);
		while (!info->end && i < info->nb_philo)
		{
			pthread_mutex_lock(&philos->info->check_dead_loop);
			if (get_time() - philos[i].time_last_eat
				> philos[i].info->time_to_die)
			{
				print_status_philo(&philos[i], "died");
				pthread_mutex_lock(&philos->info->die);
				philos[i].info->end = 1;
				pthread_mutex_unlock(&philos->info->die);
			}
			pthread_mutex_unlock(&philos->info->check_dead_loop);
			i++;
		}
		pthread_mutex_unlock(&philos->info->check_nb_philo);
	}
}

void	eating(t_philo *philos)
{
	print_status_philo(philos, "has taken a fork");
	print_status_philo(philos, "has taken a fork");
	print_status_philo(philos, "is eating");
	pthread_mutex_lock(&philos->info->check_dead_loop);
	philos->time_last_eat = get_time();
	pthread_mutex_unlock(&philos->info->check_dead_loop);
	philos->nb_eat++;
	usleep((philos->info->time_to_eat * 1000));
	if (philos->nb_eat == philos->info->must_eat)
				philos->finished_eat = 1;
}

void	*process(void *philos)
{
	while (1)
	{
		eat_philo((t_philo *)philos);
		sleep_philo((t_philo *)philos);
		think_philo((t_philo *)philos);
		pthread_mutex_lock(&((t_philo *)philos)->info->check_dead_loop);
		if (((t_philo *)philos)->info->end == 1
			|| ((t_philo *)philos)->finished_eat == 1)
		{
			pthread_mutex_unlock(&((t_philo *)philos)->info->check_dead_loop);
			break ;
		}
		pthread_mutex_unlock(&((t_philo *)philos)->info->check_dead_loop);
		usleep(50);
	}
	return (NULL);
}

void	philo_process(t_info *info, char **av, t_philo *philos)
{
	int			i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&philos->philo[i], NULL, process, &philos[i]) != 0)
			perror("Error");
		usleep(100);
		i++;
	}
	check_dead_philo(info, philos);
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		if (pthread_join(philos->philo[i], NULL) != 0)
			perror("Error");
	}
}

void	think_philo(t_philo *philos)
{
	print_status_philo(philos, "is tinking");
}
