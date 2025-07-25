/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 04:29:56 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/28 13:32:09 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

t_point	start_point(t_map *head)
{
	size_t	i;
	t_point	rv;

	i = 0;
	while (head->line[i] != '1')
		i++;
	rv.x = i;
	rv.y = 0;
	return (rv);
}

int	map_algorythm(t_map *m, t_point *start, t_point p, t_direction from);

int	map_algorythm2(t_map *m, t_point *start, t_point p, t_direction from)
{
	if (from != west)
	{
		if (p.x - 1 >= 0 && m->line[(int)p.x - 1] == '1')
			if (map_algorythm(m, start, (t_point){p.x - 1, p.y}, east))
				return (m->line[(int)p.x] = '1', 1);
	}
	if (from != north)
	{
		if (m->prev && p.x < ft_strlen(m->prev->line)
			&& m->prev->line[(int)p.x] == '1')
			if (map_algorythm(m->prev, start, (t_point){p.x, p.y + 1}, south))
				return (m->line[(int)p.x] = '1', 1);
	}
	if (from != south)
	{
		if (m->next && p.x < ft_strlen(m->next->line)
			&& m->next->line[(int)p.x] == '1')
			if (map_algorythm(m->next, start, (t_point){p.x, p.y - 1}, north))
				return (m->line[(int)p.x] = '1', 1);
	}
	return (m->line[(int)p.x] = '1', 0);
}

int	map_algorythm(t_map *m, t_point *start, t_point p, t_direction from)
{
	if (from == none)
	{
		p.x = start->x;
		p.y = start->y;
	}
	else if (p.x == start->x && p.y == start->y)
		return (1);
	else
		m->line[(int)p.x] = '0';
	if (from != east)
	{
		if (p.x + 1 < ft_strlen(m->line) && m->line[(int)p.x + 1] == '1')
			if (map_algorythm(m, start, (t_point){p.x + 1, p.y}, west))
				return (m->line[(int)p.x] = '1', 1);
	}
	return (map_algorythm2(m, start, p, from));
}

int	check_boundaries(t_map *head)
{
	t_point	start;

	start = start_point(head);
	return (map_algorythm(head, &start, (t_point){0, 0}, none));
}
