/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:02:50 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/16 11:38:15 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

long	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	result;

	result = 0;
	neg = 1;
	i = 0;
	while (str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ' )
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
				neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
			result = (result * 10) + str[i] - '0';
			i++;
	}
	return (result * neg);
}

int	get_time(void)
{
	struct timeval	t_return;

	gettimeofday(&t_return, NULL);
	return ((t_return.tv_sec * 1000000 + t_return.tv_usec) / 1000);
}

void	print_status_philo(t_philo *philos, char *message)
{
	pthread_mutex_lock(&philos->info->mutex_print);
	pthread_mutex_lock(&philos->info->check_dead);
	pthread_mutex_lock(&philos->info->die);
	if (philos->info->end == 0 && philos->finished_eat == 0)
		printf("%d %d %s\n", get_time() - philos->info->begin_time,
			philos->id_philo, message);
	pthread_mutex_unlock(&philos->info->die);
	pthread_mutex_unlock(&philos->info->check_dead);
	pthread_mutex_unlock(&philos->info->mutex_print);
}
