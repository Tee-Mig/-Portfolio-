/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_perso3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:56:16 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 12:59:41 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	perso_gauche(t_game *game)
{
	if (game->pos_perso == 0)
		perso_gauche1(game);
	else if (game->pos_perso == 1)
		perso_gauche2(game);
	else if (game->pos_perso == 2)
		perso_gauche3(game);
	else if (game->pos_perso == 3)
	{
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_image(game->mlx_ptr, game->img_start_player);
		game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
				"./images/sprites/perso/gauche/perso2_g_b.xpm",
				&game->img_width, &game->img_height);
		draw_map(game);
		game->pos_perso = -1;
	}
}

void	perso_gauche1(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_start_player);
	game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/perso/gauche/perso1_g_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}

void	perso_gauche2(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_start_player);
	game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/perso/gauche/perso2_g_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}

void	perso_gauche3(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_start_player);
	game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/perso/gauche/perso3_g_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}
