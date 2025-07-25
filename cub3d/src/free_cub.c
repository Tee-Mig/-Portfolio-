/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:22:52 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 10:54:32 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

#ifdef BONUS

void	free_cub2(t_cub *cub)
{
	if (cub->no_texture)
		free_texture(cub->no_texture);
	if (cub->so_texture)
		free_texture(cub->so_texture);
	if (cub->we_texture)
		free_texture(cub->we_texture);
	if (cub->ea_texture)
		free_texture(cub->ea_texture);
	if (cub->do_texture)
		free_texture(cub->do_texture);
}
#else

void	free_cub2(t_cub *cub)
{
	if (cub->no_texture)
		free_texture(cub->no_texture);
	if (cub->so_texture)
		free_texture(cub->so_texture);
	if (cub->we_texture)
		free_texture(cub->we_texture);
	if (cub->ea_texture)
		free_texture(cub->ea_texture);
}
#endif

void	free_cub(t_cub *cub)
{
	if (cub->rays)
		free_rays(cub->rays);
	if (cub->w_head)
		free_walls(cub->w_head);
	if (cub->m_head)
		free_map(cub->m_head);
	if (cub->img)
	{
		mlx_destroy_image(cub->mlx, cub->img->img);
		free(cub->img);
	}
	if (cub->mlx_win)
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	if (cub->player)
		free_player(cub->player);
	free_cub2(cub);
	free(cub);
}
