/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:23:30 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 10:25:50 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

size_t	get_xoffset(t_wall *head)
{
	t_wall	*w;
	size_t	rv;

	w = head;
	rv = 2147483647;
	while (w)
	{
		if (w->start->x < rv)
			rv = w->start->x;
		w = w->next;
	}
	return (rv);
}

size_t	get_yoffset(t_wall *head)
{
	t_wall	*w;
	size_t	rv;

	w = head;
	rv = 2147483647;
	while (w)
	{
		if (w->start->y < rv)
			rv = w->start->y;
		w = w->next;
	}
	return (rv);
}

float	get_xratio(t_wall *head)
{
	size_t	x;
	t_wall	*w;

	w = head;
	x = 0;
	while (w)
	{
		if (w->end->x > x)
			x = w->end->x;
		w = w->next;
	}
	return (x / (WIDTH / 10));
}

float	get_yratio(t_wall *head)
{
	size_t	x;
	t_wall	*w;

	w = head;
	x = 0;
	while (w)
	{
		if (w->end->y > x)
			x = w->end->y;
		w = w->next;
	}
	return (x / (HEIGHT / 10));
}
