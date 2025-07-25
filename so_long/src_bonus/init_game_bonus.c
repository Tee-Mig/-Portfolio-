/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:58:14 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 13:15:53 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_window_size(t_game *game)
{
	int	i;

	game->win_width = ft_strlen(game->map[0]) * 32;
	i = 0;
	while (game->map[i])
		i++;
	game->win_height = i * 32 + 32;
}

void	init_img(t_game *game)
{
	game->img_wall = mlx_xpm_file_to_image(game->mlx_ptr, "./images/wall_b.xpm",
			&game->img_width, &game->img_height);
	game->img_start_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/perso/droit/perso1_d_b.xpm",
			&game->img_width, &game->img_height);
	game->img_item = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/collect_b.xpm", &game->img_width, &game->img_height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/exit_b.xpm", &game->img_width, &game->img_height);
	game->img_empty = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/grass.xpm", &game->img_width, &game->img_height);
	game->img_ennemy = mlx_xpm_file_to_image(game->mlx_ptr,
			"./images/sprites/ennemy/gauche/ennemy1_g_b.xpm", &game->img_width,
			&game->img_height);
}

void	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	set_window_size(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->win_width,
			game->win_height, "so_long");
	game->end = 0;
	game->loop_anim_perso = 0;
	game->loop_anim_ennemy = 0;
	game->nb_move = 0;
	game->sens_perso = 1;
	game->pos_perso = 0;
	game->sens_ennemy = 0;
	game->pos_ennemy = 0;
	init_img(game);
	draw_map(game);
	print_moves(game);
}
