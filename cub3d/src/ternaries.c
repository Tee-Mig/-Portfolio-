/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternaries.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 21:33:53 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/20 21:35:01 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	int_ternary(int condition, int true_value, int false_value)
{
	if (condition)
		return (true_value);
	return (false_value);
}

float	float_ternary(float condition, float true_value, float false_value)
{
	if (condition)
		return (true_value);
	return (false_value);
}
