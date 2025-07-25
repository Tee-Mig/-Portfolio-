/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_presskey_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 11:05:39 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 15:02:39 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_presskey(int key, t_game *game)
{
	if (key == 'w')
		z_key_pressed(game);
	if (key == 'a')
		q_key_pressed(game);
	if (key == 'd')
		d_key_pressed(game);
	if (key == 's')
		s_key_pressed(game);
	if (game->end == 1)
		close_game(game);
}
