/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:04:37 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 13:32:46 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	img_draw(t_game *game, void *image, int x, int y)
{
	mlx_put_image_to_window
		(game->mlx_ptr, game->win_ptr, image, x * 32, y * 32 + 32);
}

void	draw_player(t_game *game, void *image, int x, int y)
{
	game->player_x = y;
	game->player_y = x;
	mlx_put_image_to_window
		(game->mlx_ptr, game->win_ptr, image, x * 32, y * 32 + 32);
}

void	draw_exit(t_game *game, int x, int y)
{
	if (game->nb_img_item == 0)
	{
		mlx_destroy_image(game->mlx_ptr, game->img_exit);
		game->img_exit = mlx_xpm_file_to_image(game->mlx_ptr,
				"./images/exit_b2.xpm", &game->img_width,
				&game->img_height);
	}
	img_draw(game, game->img_exit, x, y);
}

int	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == '1')
				img_draw(game, game->img_wall, x, y);
			else if (game->map[y][x] == 'P')
				draw_player(game, game->img_start_player, x, y);
			else if (game->map[y][x] == 'C')
				img_draw(game, game->img_item, x, y);
			else if (game->map[y][x] == 'E')
				draw_exit(game, x, y);
			else if (game->map[y][x] == '0')
				img_draw(game, game->img_empty, x, y);
			else if (game->map[y][x] == 'X')
				img_draw(game, game->img_ennemy, x, y);
		}
	}
	print_moves_draw(game);
	return (0);
}
