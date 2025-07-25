/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_presskey2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:15:47 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 16:18:23 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	z_key_pressed(t_game *game)
{
	if (game->map[game->player_x - 1][game->player_y] == '0')
	{
		game->nb_move++;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		game->player_x--;
		game->map[game->player_x][game->player_y] = 'P';
		game->map[game->player_x + 1][game->player_y] = '0';
		draw_map(game);
		print_moves(game);
	}
	else if (game->map[game->player_x - 1][game->player_y] == 'C')
	{
		game->nb_move++;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		game->player_x--;
		game->map[game->player_x][game->player_y] = 'P';
		game->map[game->player_x + 1][game->player_y] = '0';
		game->nb_img_item--;
		draw_map(game);
		print_moves(game);
	}
	else if (game->map[game->player_x - 1][game->player_y] == 'E'
		&& game->nb_img_item == 0)
		end_message(game);
}

void	q_key_pressed(t_game *game)
{
	if (game->map[game->player_x][game->player_y - 1] == '0')
	{
		q_key_pressed2(game);
		print_moves(game);
	}
	else if (game->map[game->player_x][game->player_y - 1] == 'C')
	{
		q_key_pressed2(game);
		game->nb_img_item--;
		print_moves(game);
	}
	else if (game->map[game->player_x][game->player_y - 1] == 'E'
		&& game->nb_img_item == 0)
		end_message(game);
}

void	d_key_pressed(t_game *game)
{
	if (game->map[game->player_x][game->player_y + 1] == '0')
	{
		d_key_pressed2(game);
		print_moves(game);
	}
	else if (game->map[game->player_x][game->player_y + 1] == 'C')
	{
		d_key_pressed2(game);
		game->nb_img_item--;
		print_moves(game);
	}
	else if (game->map[game->player_x][game->player_y + 1] == 'E'
		&& game->nb_img_item == 0)
		end_message(game);
}

void	s_key_pressed(t_game *game)
{
	if (game->map[game->player_x + 1][game->player_y] == '0')
	{
		game->nb_move++;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		game->player_x++;
		game->map[game->player_x][game->player_y] = 'P';
		game->map[game->player_x - 1][game->player_y] = '0';
		draw_map(game);
		print_moves(game);
	}
	else if (game->map[game->player_x + 1][game->player_y] == 'C')
	{
		game->nb_move++;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		game->player_x++;
		game->map[game->player_x][game->player_y] = 'P';
		game->map[game->player_x - 1][game->player_y] = '0';
		game->nb_img_item--;
		draw_map(game);
		print_moves(game);
	}
	else if (game->map[game->player_x + 1][game->player_y] == 'E'
		&& game->nb_img_item == 0)
		end_message(game);
}
