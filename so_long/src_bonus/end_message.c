/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:13:44 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 16:29:40 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	end_message_z(t_game *game)
{
	if (game->map[game->player_x - 1][game->player_y] == 'E'
		&& game->nb_img_item == 0)
		ft_putstr("Bien joué, tu as réussi a collecter tous les cristaux.");
	else if (game->map[game->player_x - 1][game->player_y] == 'X')
		ft_putstr("Un ennemi t'a tué. Retente ta chance.");
	game->end = 1;
}

void	end_message_q(t_game *game)
{
	if (game->map[game->player_x][game->player_y - 1] == 'E'
		&& game->nb_img_item == 0)
		ft_putstr("Bien joué, tu as réussi a collecter tous les cristaux.");
	else if (game->map[game->player_x][game->player_y - 1] == 'X')
		ft_putstr("Un ennemi t'a tué. Retente ta chance.");
	game->end = 1;
}

void	end_message_d(t_game *game)
{
	if (game->map[game->player_x][game->player_y + 1] == 'E'
		&& game->nb_img_item == 0)
		ft_putstr("Bien joué, tu as réussi a collecter tous les cristaux.");
	else if (game->map[game->player_x][game->player_y + 1] == 'X')
		ft_putstr("Un ennemi t'a tué. Retente ta chance.");
	game->end = 1;
}

void	end_message_s(t_game *game)
{
	if (game->map[game->player_x + 1][game->player_y] == 'E'
		&& game->nb_img_item == 0)
		ft_putstr("Bien joué, tu as réussi a collecter tous les cristaux.");
	else if (game->map[game->player_x + 1][game->player_y] == 'X')
		ft_putstr("Un ennemi t'a tué. Retente ta chance.");
	game->end = 1;
}
