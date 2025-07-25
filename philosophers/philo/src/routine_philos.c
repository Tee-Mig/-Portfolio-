/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:42:28 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/16 11:42:19 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_philo(t_philo *philos)
{
	while (1)
	{
		usleep(50);
		if (philos->info->nb_philo > 1)
		{
			lock_forks(philos);
			eating(philos);
			unlock_forks(philos);
			break ;
		}
		eat_philo_one(philos);
		pthread_mutex_lock(&philos->info->check_dead_process);
		pthread_mutex_lock(&philos->info->die);
		if (philos->info->end == 1 || philos->finished_eat == 1)
		{
			pthread_mutex_unlock(&philos->info->die);
			pthread_mutex_unlock(&philos->info->check_dead_process);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&philos->info->die);
			pthread_mutex_unlock(&philos->info->check_dead_process);
		}
	}
}

void	eat_philo_one(t_philo *philos)
{
	if (philos->info->nb_philo == 1 && philos->info->state_fork_one == 0)
	{
		philos->info->state_fork_one = 1;
		print_status_philo(philos, "has taken a fork");
	}
}

void	lock_forks(t_philo *philos)
{
	if (philos->id_philo == 1)
	{
		pthread_mutex_lock(&philos->info->forks[philos->left_fork]);
		pthread_mutex_lock(&philos->info->forks[philos->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philos->info->forks[philos->right_fork]);
		pthread_mutex_lock(&philos->info->forks[philos->left_fork]);
	}
}

void	unlock_forks(t_philo *philos)
{
	if (philos->id_philo == 1)
	{
		pthread_mutex_unlock(&philos->info->forks[philos->right_fork]);
		pthread_mutex_unlock(&philos->info->forks[philos->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philos->info->forks[philos->left_fork]);
		pthread_mutex_unlock(&philos->info->forks[philos->right_fork]);
	}
}

void	sleep_philo(t_philo *philos)
{
	print_status_philo(philos, "is sleeping");
	usleep((philos->info->time_to_sleep * 1000));
}
