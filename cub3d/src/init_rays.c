/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:10:54 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/28 15:28:05 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	init_rays(t_cub *cub)
{
	size_t	i;
	float	increment;
	float	angle;

	i = 0;
	angle = 0;
	increment = (float)((FOV * M_PI / 180) / WIDTH);
	if (cub->rays)
		free_rays(cub->rays);
	cub->rays = malloc(sizeof(t_ray *) * WIDTH);
	while (i < WIDTH)
	{
		cub->rays[i] = malloc(sizeof(t_ray));
		cub->rays[i]->angle = angle + (cub->player->angle * M_PI / 180)
			- (FOV * M_PI / 360);
		cub->rays[i]->dirx = cosf(cub->rays[i]->angle);
		cub->rays[i]->diry = sinf(cub->rays[i]->angle);
		cub->rays[i]->distance = 0;
		cub->rays[i]->intersection = closest_intersection(cub->player,
				cub->rays[i], cub->w_head);
		angle += increment;
		i++;
	}
}
