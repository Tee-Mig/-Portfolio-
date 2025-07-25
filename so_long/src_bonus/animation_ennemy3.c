/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_ennemy3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:03:29 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 13:20:04 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ennemy_gauche(t_game *game)
{
	if (game->pos_ennemy == 0)
		ennemy_gauche1(game);
	else if (game->pos_ennemy == 1)
		ennemy_gauche2(game);
	else if (game->pos_ennemy == 2)
		ennemy_gauche3(game);
	else if (game->pos_ennemy == 3)
	{
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_image(game->mlx_ptr, game->img_ennemy);
		game->img_ennemy = mlx_xpm_file_to_image(game->mlx_ptr,
				"./images/sprites/ennemy/gauche/ennemy2_g_b.xpm",
				&game->img_width, &game->img_height);
		draw_map(game);
		game->pos_ennemy = -1;
	}
}

void	ennemy_gauche1(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_ennemy);
	game->img_ennemy = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/ennemy/gauche/ennemy1_g_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}

void	ennemy_gauche2(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_ennemy);
	game->img_ennemy = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/ennemy/gauche/ennemy2_g_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}

void	ennemy_gauche3(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_ennemy);
	game->img_ennemy = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/ennemy/gauche/ennemy3_g_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}
