/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:37:10 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/16 11:20:15 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	parsing(int ac, char **av)
{
	int	error_parsing;

	error_parsing = 1;
	if (only_number_and_overflow1(av[1], &error_parsing) == 0)
		ft_putstr("Error: number of philosophers\n");
	if (ft_atoi(av[1]) == 0)
		print_error(&error_parsing, "Error: number of philosophers\n");
	if (only_number_and_overflow1(av[2], &error_parsing) == 0)
		ft_putstr("Error: time to die\n");
	if (only_number_and_overflow1(av[3], &error_parsing) == 0)
		ft_putstr("Error: time to eat\n");
	if (only_number_and_overflow1(av[4], &error_parsing) == 0)
		ft_putstr("Error: time to sleep\n");
	if (ac == 6)
	{
		if (only_number_and_overflow1(av[5], &error_parsing) == 0
			|| ft_atoi(av[5]) == 0)
			print_error(&error_parsing,
				"Error: number of time each philosopher must eat\n");
	}
	return (error_parsing);
}

void	print_error(int *error_parsing, char *str_error)
{
	printf("%s", str_error);
	*error_parsing = 0;
}

//regler norminette parsing !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int	only_number_and_overflow1(char *str, int *error_parsing)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' && ft_atoi(str) != 0)
	{
		*error_parsing = 0;
		return (0);
	}
	else
		i++;
	while (str[i] == '0')
		i++;
	if (only_number_and_overflow2(str, &*error_parsing, i) == 0)
		return (0);
	return (1);
}

int	only_number_and_overflow2(char *str, int *error_parsing, int i)
{
	int	len;

	len = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		len++;
	}
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
	{
		*error_parsing = 0;
		return (0);
	}
	if (only_number_and_overflow3(str, error_parsing, len) == 0)
		return (0);
	return (1);
}

int	only_number_and_overflow3(char *str, int *error_parsing, int len)
{
	if (len > 10)
	{
		*error_parsing = 0;
		return (0);
	}
	if (ft_atoi(str) > 2147483647)
	{
		*error_parsing = 0;
		return (0);
	}
	return (1);
}
