/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_presskey.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 11:05:39 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/24 16:39:31 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_presskey(int key, t_game *game)
{
	if (key == 'w' || key == 38)
		z_key_pressed(game);
	if (key == 'a' || key == 37)
		q_key_pressed(game);
	if (key == 'd' || key == 39)
		d_key_pressed(game);
	if (key == 's' || key == 40)
		s_key_pressed(game);
	if (game->end == 1)
		close_game(game);
}
