/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:18:52 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 13:33:19 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	print_moves(t_game *game)
{
	char	*moves;

	moves = ft_itoa(game->nb_move);
	ft_putstr("MOVES: ");
	ft_putnbr(game->nb_move);
	ft_putchar('\n');
	mlx_string_put(game->mlx_ptr, game->win_ptr, 15, 21, 0xFFFFFFFF, "MOVES: ");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 60, 21,
		0xFFFFFFFF, moves);
	free(moves);
}

void	print_moves_draw(t_game *game)
{
	char	*moves;

	moves = ft_itoa(game->nb_move);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 15, 21, 0xFFFFFFFF, "MOVES: ");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 60, 21,
		0xFFFFFFFF, moves);
	free(moves);
}
