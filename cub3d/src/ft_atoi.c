/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 07:24:00 by ccambium          #+#    #+#             */
/*   Updated: 2021/10/31 07:24:00 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	ft_atoi_part2(int i, int minus, const char *nptr)
{
	int	v;

	v = 0;
	while (*(nptr + i) && ft_isdigit(*(nptr + i)))
	{
		v *= 10;
		v += *(nptr + i) - '0';
		i++;
	}
	if (minus)
		v *= -1;
	return (v);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	minus;

	i = 0;
	minus = 0;
	while (*(nptr + i) == '\f' || *(nptr + i) == '\n' || *(nptr + i) == '\r'
		|| *(nptr + i) == '\t' || *(nptr + i) == '\v' || *(nptr + i) == ' ')
		i++;
	if (*(nptr + i) == '-')
	{
		i++;
		minus = 1;
	}
	else if (*(nptr + i) == '+')
		i++;
	return (ft_atoi_part2(i, minus, nptr));
}
