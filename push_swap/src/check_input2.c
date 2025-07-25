/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:28:37 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/11 19:37:45 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_check_overflow(char **av, int input_status)
{
	int	i;
	int	j;

	i = -1;
	if (input_status == 1)
	{
		while (av[++i])
		{
			j = 0;
			while (av[i][j] == ' ')
				j++;
			if (av[i][j] == '-' && nb_count(ft_atoi(av[i])) > 11)
				return (0);
			else if (av[i][j] != '-' && nb_count(ft_atoi(av[i])) > 10)
				return (0);
			else if (ft_atoi(av[i]) > 2147483647
				|| ft_atoi(av[i]) < -2147483648)
				return (0);
		}
		return (1);
	}
	else
		return (0);
	return (0);
}

void	second_check(int *input_status, int *ac, char **av)
{
	if (*ac == 2)
		*input_status = ft_check_overflow(av, *input_status);
	else if (*ac > 2)
		*input_status = ft_check_overflow(av + 1, *input_status);
}
