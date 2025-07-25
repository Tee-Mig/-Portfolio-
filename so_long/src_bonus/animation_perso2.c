/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_perso2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:00:23 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 13:08:07 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	perso_droit(t_game *game)
{
	if (game->pos_perso == 0)
		perso_droit1(game);
	else if (game->pos_perso == 1)
		perso_droit2(game);
	else if (game->pos_perso == 2)
		perso_droit3(game);
	else if (game->pos_perso == 3)
	{
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_image(game->mlx_ptr, game->img_start_player);
		game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
				"./images/sprites/perso/droit/perso2_d_b.xpm",
				&game->img_width, &game->img_height);
		draw_map(game);
		game->pos_perso = -1;
	}
}

void	perso_droit1(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_start_player);
	game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/perso/droit/perso1_d_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}

void	perso_droit2(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_start_player);
	game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/perso/droit/perso2_d_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}

void	perso_droit3(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_start_player);
	game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/perso/droit/perso3_d_b.xpm",
			&game->img_width, &game->img_height);
	draw_map(game);
}
