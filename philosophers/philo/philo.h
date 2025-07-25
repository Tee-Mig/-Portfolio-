/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:23:34 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/16 11:35:53 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				end;
	int				must_eat;
	int				begin_time;
	int				state_fork_one;
	pthread_mutex_t	check_nb_philo;
	pthread_mutex_t	die;
	pthread_mutex_t	check_dead_process;
	pthread_mutex_t	check_dead_loop;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*forks;
}	t_info;

typedef struct s_philo
{
	int			right_fork;
	int			left_fork;
	int			nb_eat;
	int			id_philo;
	int			time_last_eat;
	int			finished_eat;
	pthread_t	*philo;
	t_info		*info;
}	t_philo;

void	philo_process(t_info *info, char **av, t_philo *philos);
void	*process(void *philos);
int		fill_info(char **av, t_info *info, t_philo *philos);
void	fill_info2(t_info *info, t_philo *philos);
int		parsing(int ac, char **av);
long	ft_atoi(const char *str);
int		only_number_and_overflow1(char *str, int *error_parsing);
int		ft_strlen(char *str);
void	ft_putstr(char *str);
int		get_time(void);
void	free_all_end(t_info *info, t_philo *philos);
int		error_malloc_struct(t_info *info, t_philo *philos);
void	eating(t_philo *philos);
void	lock_forks(t_philo *philos);
void	unlock_forks(t_philo *philos);
void	eat_philo(t_philo *philos);
void	sleep_philo(t_philo *philos);
void	think_philo(t_philo *philos);
void	print_status_philo(t_philo *philos, char *message);
int		error_malloc_info(t_info *info, t_philo *philos);
void	print_error(int *error_parsing, char *str_error);
int		only_number_and_overflow2(char *str, int *error_parsing, int i);
int		only_number_and_overflow3(char *str, int *error_parsing, int len);
void	eat_philo_one(t_philo *philos);

#endif