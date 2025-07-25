/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   does_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:32:03 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 08:30:37 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static t_point	*calculate(t_calculate *calc)
{
	float		t;
	float		u;
	float		den;
	t_point		*point;

	den = (calc->x1 - calc->x2) * (calc->y3 - calc->y4)
		- (calc->y1 - calc->y2) * (calc->x3 - calc->x4);
	if (den == 0)
		return (NULL);
	t = ((calc->x1 - calc->x3) * (calc->y3 - calc->y4)
			- (calc->y1 - calc->y3) * (calc->x3 - calc->x4)) / den;
	u = -((calc->x1 - calc->x2) * (calc->y1 - calc->y3)
			- (calc->y1 - calc->y2) * (calc->x1 - calc->x3)) / den;
	if (t >= 0 && t <= 1 && u >= 0)
	{
		point = malloc(sizeof(t_point));
		if (!point)
			return (NULL);
		point->x = calc->x1 + t * (calc->x2 - calc->x1);
		point->y = calc->y1 + t * (calc->y2 - calc->y1);
		return (point);
	}
	return (NULL);
}

#ifdef BONUS

t_point	*does_intersect(t_player *player, t_ray *ray, t_wall *wall)
{
	t_calculate	calc;

	if (wall->type != door)
	{
		calc.x1 = wall->start->x;
		calc.y1 = wall->start->y;
		calc.x2 = wall->end->x;
		calc.y2 = wall->end->y;
	}
	else
	{
		calc.x1 = wall->start->x + wall->offsetx;
		calc.y1 = wall->start->y + wall->offsety;
		calc.x2 = wall->end->x + wall->offsetx;
		calc.y2 = wall->end->y + wall->offsety;
	}
	calc.x3 = player->pos->x;
	calc.y3 = player->pos->y;
	calc.x4 = player->pos->x + ray->dirx;
	calc.y4 = player->pos->y + ray->diry;
	return (calculate(&calc));
}
#else

t_point	*does_intersect(t_player *player, t_ray *ray, t_wall *wall)
{
	t_calculate	calc;

	calc.x1 = wall->start->x;
	calc.y1 = wall->start->y;
	calc.x2 = wall->end->x;
	calc.y2 = wall->end->y;
	calc.x3 = player->pos->x;
	calc.y3 = player->pos->y;
	calc.x4 = player->pos->x + ray->dirx;
	calc.y4 = player->pos->y + ray->diry;
	return (calculate(&calc));
}
#endif
