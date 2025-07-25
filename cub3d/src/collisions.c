/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:48:27 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 10:28:47 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static float	cast(t_cub *cub, float angle, t_wall *walls)
{
	t_ray		*cast;
	float		dist;

	cast = malloc(sizeof(t_ray));
	cast->angle = angle;
	cast->dirx = cosf(cast->angle);
	cast->diry = sinf(cast->angle);
	cast->distance = 0;
	free(closest_intersection(cub->player, cast, walls));
	dist = cast->distance;
	free(cast);
	return (dist);
}

int	will_collide(t_cub *cub, t_direction dir)
{
	float	dist;

	dist = 0;
	if (dir == north)
		dist = cub->rays[WIDTH / 2]->distance;
	if (dir == south)
		dist = cast(cub, cub->rays[WIDTH / 2]->angle + M_PI, cub->w_head);
	if (dir == east)
		dist = cast(cub, cub->rays[WIDTH / 2]->angle + M_PI / 2, cub->w_head);
	if (dir == west)
		dist = cast(cub, cub->rays[WIDTH / 2]->angle - M_PI / 2, cub->w_head);
	return (dist < (float)10);
}
