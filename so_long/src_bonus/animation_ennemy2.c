/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_ennemy2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:03:23 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 13:14:47 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ennemy_droit(t_game *game)
{
	if (game->pos_ennemy == 0)
		ennemy_droit1(game);
	else if (game->pos_ennemy == 1)
		ennemy_droit2(game);
	else if (game->pos_ennemy == 2)
		ennemy_droit3(game);
	else if (game->pos_ennemy == 3)
	{
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_image(game->mlx_ptr, game->img_ennemy);
		game->img_ennemy = mlx_xpm_file_to_image(game->mlx_ptr,
				"./images/sprites/ennemy/droit/ennemy2_d_b.xpm",
				&game->img_width, &game->img_height);
		draw_map(game);
		game->pos_ennemy = -1;
	}
}

void	ennemy_droit1(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_ennemy);
	game->img_ennemy = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/ennemy/droit/ennemy1_d_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}

void	ennemy_droit2(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_ennemy);
	game->img_ennemy = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/ennemy/droit/ennemy2_d_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}

void	ennemy_droit3(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_ennemy);
	game->img_ennemy = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/ennemy/droit/ennemy3_d_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}
