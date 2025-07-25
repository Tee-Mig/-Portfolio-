/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:42:39 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 14:26:44 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

char	check_colors(char **colors)
{
	size_t	i;

	i = -1;
	while (colors[0][++i])
	{
		if (!is_digit(colors[0][i]))
			return (free_split(colors), 1);
	}
	i = -1;
	while (colors[1][++i])
	{
		if (!is_digit(colors[1][i]))
			return (free_split(colors), 1);
	}
	i = -1;
	while (colors[2][++i])
	{
		if (!is_digit(colors[2][i]))
			return (free_split(colors), 1);
	}
	return (0);
}

char	check_valid_rgb(char **colors)
{
	int	x;

	if (ft_strlen(colors[0]) > 3
		|| ft_strlen(colors[1]) > 3
		|| ft_strlen(colors[2]) > 3)
		return (1);
	x = ft_atoi(colors[0]);
	if (x > 255)
		return (1);
	x = ft_atoi(colors[1]);
	if (x > 255)
		return (1);
	x = ft_atoi(colors[2]);
	if (x > 255)
		return (1);
	return (0);
}
