/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:31:38 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/28 15:48:10 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	open_door(t_cub *cub)
{
	if (!cub->rays[WIDTH / 2]->wall)
		return (0);
	if (cub->rays[WIDTH / 2]->wall->type != door)
		return (0);
	if (cub->rays[WIDTH / 2]->distance >= 80)
		return (0);
	if (cub->rays[WIDTH / 2]->wall->state == opened
		|| cub->rays[WIDTH / 2]->wall->state == opening)
		cub->rays[WIDTH / 2]->wall->state = closing;
	else if (cub->rays[WIDTH / 2]->wall->state == closed
		|| cub->rays[WIDTH / 2]->wall->state == closing)
		cub->rays[WIDTH / 2]->wall->state = opening;
	return (0);
}

static void	dopening(t_wall *wall, t_direction dir)
{
	if (dir == north)
	{
		wall->offsetx -= 1;
		if (wall->offsetx == -TILE + 10)
			wall->state = opened;
	}
	else if (dir == south)
	{
		wall->offsetx += 1;
		if (wall->offsetx == TILE - 10)
			wall->state = opened;
	}
	else if (dir == east)
	{
		wall->offsety += 1;
		if (wall->offsety == TILE - 10)
			wall->state = opened;
	}
	else if (dir == west)
	{
		wall->offsety -= 1;
		if (wall->offsety == -TILE + 10)
			wall->state = opened;
	}
}

static void	dclosing(t_wall *wall, t_direction dir)
{
	if (dir == north)
	{
		wall->offsetx += 1;
		if (wall->offsetx == 0)
			wall->state = closed;
	}
	else if (dir == south)
	{
		wall->offsetx -= 1;
		if (wall->offsetx == 0)
			wall->state = closed;
	}
	else if (dir == east)
	{
		wall->offsety -= 1;
		if (wall->offsety == 0)
			wall->state = closed;
	}
	else if (dir == west)
	{
		wall->offsety += 1;
		if (wall->offsety == 0)
			wall->state = closed;
	}
}

static void	add_offset(t_wall *wall, t_direction dir)
{
	if (wall->state == opening)
		dopening(wall, dir);
	else if (wall->state == closing)
		dclosing(wall, dir);
}

void	move_doors(t_wall *walls)
{
	t_wall	*w;

	w = walls;
	while (w)
	{
		if (w->type == door)
			add_offset(w, w->direction);
		w = w->next;
	}
}
