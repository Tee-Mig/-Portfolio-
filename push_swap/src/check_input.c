/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:12:18 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/20 16:52:29 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	is_only_sign(char *input)
{
	int	i;
	int	space;
	int	sign;

	i = -1;
	space = 0;
	sign = 0;
	while (input[++i])
		if (input[i] == '-' || input[i] == '+')
			sign++;
	i = -1;
	while (input[++i])
		if (input[i] == ' ')
			space++;
	if (((space + sign) == ft_strlen(input)) && (is_full_space(input) == 0))
		return (1);
	return (0);
}

int	is_full_space(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (i == ft_strlen(input))
		return (1);
	return (0);
}

int	check_input_args2(int *i, int *j, char **user_input)
{
	int	nb_count;

	nb_count = 0;
	while (user_input[*j][*i] == ' ')
		*i += 1;
	if (user_input[*j][*i] == '+' || user_input[*j][*i] == '-')
		*i += 1;
	while (user_input[*j][*i] == '0')
		*i += 1;
	while (user_input[*j][*i] >= '0' && user_input[*j][*i] <= '9')
	{
		*i += 1;
		nb_count++;
	}
	while (user_input[*j][*i] == ' ')
		*i += 1;
	return (nb_count);
}

int	check_input_args(char **user_input, t_dlist **stack_a, t_dlist **sb)
{
	int	i;
	int	j;

	j = -1;
	while (user_input[++j])
	{
		i = 0;
		if (check_input_args2(&i, &j, user_input) > 10)
			return (0);
		if (user_input[j][i] != '\0' || is_only_sign(user_input[j]))
			return (0);
		if (user_input[j][0] != '\0' && is_full_space(user_input[j]) == 0)
			ft_add_last(&*stack_a, ft_atoi(user_input[j]), &*sb);
	}
	if (check_double(user_input))
		return (1);
	return (0);
}

int	check_double(char **user_input)
{
	int	i;
	int	j;

	j = 0;
	while (user_input[j])
	{
		i = j + 1;
		if (is_full_space(user_input[j]) == 0)
		{
			while (user_input[i])
			{
				if (is_full_space(user_input[i]) == 0)
					if (ft_atoi(user_input[j]) == ft_atoi(user_input[i]))
						return (0);
				i++;
			}
		}
		j++;
	}
	return (1);
}
