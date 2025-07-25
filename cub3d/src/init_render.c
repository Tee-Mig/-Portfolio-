/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:37:42 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/28 13:14:53 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

#ifdef BONUS

static void	get_wallx(t_cub *cub, size_t i, t_render *render)
{
	if (cub->rays[i]->wall->direction == north)
		render->wallx = (int)(cub->rays[i]->intersection->x
				- cub->rays[i]->wall->offsetx)
			% cub->no_texture->width;
	if (cub->rays[i]->wall->direction == south)
		render->wallx = (int)(cub->rays[i]->intersection->x
				- cub->rays[i]->wall->offsetx
				- cub->rays[i]->wall->start->x)
			% cub->so_texture->width;
	if (cub->rays[i]->wall->direction == east)
		render->wallx = (int)(cub->rays[i]->intersection->y
				- cub->rays[i]->wall->offsety
				- cub->rays[i]->wall->start->y)
			% cub->ea_texture->width;
	if (cub->rays[i]->wall->direction == west)
		render->wallx = (int)(cub->rays[i]->intersection->y
				- cub->rays[i]->wall->offsety)
			% cub->we_texture->width;
}

static void	get_sprite(size_t i, t_render *render, t_cub *cub)
{
	if (cub->rays[i]->wall->direction == north)
		render->sprite = cub->no_texture;
	if (cub->rays[i]->wall->direction == south)
		render->sprite = cub->so_texture;
	if (cub->rays[i]->wall->direction == east)
		render->sprite = cub->ea_texture;
	if (cub->rays[i]->wall->direction == west)
		render->sprite = cub->we_texture;
	if (cub->rays[i]->wall->type == door)
		render->sprite = cub->do_texture;
}
#else

static void	get_wallx(t_cub *cub, size_t i, t_render *render)
{
	if (cub->rays[i]->wall->direction == north)
		render->wallx = (int)cub->rays[i]->intersection->x
			% cub->no_texture->width;
	if (cub->rays[i]->wall->direction == south)
		render->wallx = (int)(cub->rays[i]->intersection->x
				- cub->rays[i]->wall->start->x)
			% cub->so_texture->width;
	if (cub->rays[i]->wall->direction == east)
		render->wallx = (int)(cub->rays[i]->intersection->y
				- cub->rays[i]->wall->start->y)
			% cub->ea_texture->width;
	if (cub->rays[i]->wall->direction == west)
		render->wallx = (int)cub->rays[i]->intersection->y
			% cub->we_texture->width;
}

static void	get_sprite(size_t i, t_render *render, t_cub *cub)
{
	if (cub->rays[i]->wall->direction == north)
		render->sprite = cub->no_texture;
	if (cub->rays[i]->wall->direction == south)
		render->sprite = cub->so_texture;
	if (cub->rays[i]->wall->direction == east)
		render->sprite = cub->ea_texture;
	if (cub->rays[i]->wall->direction == west)
		render->sprite = cub->we_texture;
}

#endif

void	init_render(size_t i, t_render *render, t_cub *cub)
{
	float	projection_plane;

	if (!cub->rays[i]->intersection)
	{
		ft_bzero(render, sizeof(t_render));
		return ;
	}
	projection_plane = (WIDTH / 2) / tan((FOV / 2) * (M_PI / 180));
	render->line_h = (TILE / cub->rays[i]->distance) * projection_plane;
	if (render->line_h <= 0)
		render->line_h = 0;
	get_sprite(i, render, cub);
	render->wallstart = float_ternary(render->line_h > HEIGHT, 0,
			(HEIGHT - render->line_h) / 2);
	render->wallend = float_ternary(render->line_h > HEIGHT, HEIGHT,
			(HEIGHT + render->line_h) / 2);
	render->wally = float_ternary(render->line_h > HEIGHT,
			(render->line_h - HEIGHT)
			* (render->sprite->height / render->line_h) / 2, 0);
	render->stepy = float_ternary(render->line_h > HEIGHT,
			(render->sprite->height - render->wally
				/ render->sprite->height)
			/ render->line_h, render->sprite->height / render->line_h);
	get_wallx(cub, i, render);
}
