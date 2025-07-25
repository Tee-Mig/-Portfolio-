/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_forward.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:48:31 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 10:16:15 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

#ifdef BONUS

void	move_forward(t_cub *cub)
{
	if (will_collide(cub, north))
		return ;
	cub->player->pos->x += cub->rays[WIDTH / 2]->dirx * 3;
	cub->player->pos->y += cub->rays[WIDTH / 2]->diry * 3;
}

#else

void	move_forward(t_cub *cub)
{
	cub->player->pos->x += cub->rays[WIDTH / 2]->dirx * 3;
	cub->player->pos->y += cub->rays[WIDTH / 2]->diry * 3;
}

#endif
