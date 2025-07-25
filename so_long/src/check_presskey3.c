/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_presskey3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 23:04:34 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/24 16:26:51 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	q_key_pressed2(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img_start_player);
	game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/perso/gauche/perso1_g_b.xpm", &game->img_width,
			&game->img_height);
	game->nb_move++;
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	game->player_y--;
	game->map[game->player_x][game->player_y] = 'P';
	game->map[game->player_x][game->player_y + 1] = '0';
	draw_map(game);
}

void	d_key_pressed2(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img_start_player);
	game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/perso/droit/perso1_d_b.xpm", &game->img_width,
			&game->img_height);
	game->nb_move++;
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	game->player_y++;
	game->map[game->player_x][game->player_y] = 'P';
	game->map[game->player_x][game->player_y - 1] = '0';
	draw_map(game);
}
