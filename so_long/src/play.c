/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:45:57 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/21 10:46:19 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(t_game *game)
{
	destroy_all_img(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free_map(game->map);
	game->win_ptr = NULL;
	exit(1);
	return (0);
}

static int	presskey(int key, t_game *game)
{
	if (key == XK_Escape)
	{
		destroy_all_img(game);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		free_map(game->map);
		game->win_ptr = NULL;
		exit(1);
	}
	else if (game->end == 0)
		check_presskey(key, game);
	return (0);
}

void	play(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, presskey, game);
	mlx_hook(game->win_ptr, 17, 1L << 17, close_game, game);
	mlx_hook(game->win_ptr, 9, 1L << 21, draw_map, game);
	mlx_loop(game->mlx_ptr);
}
