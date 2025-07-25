/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_ennemy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:36:49 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 15:05:24 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	animation_ennemy(t_game *game)
{
	while (game->loop_anim_ennemy < 6000)
	{
		game->loop_anim_ennemy++;
		return ;
	}
	game->loop_anim_ennemy = 0;
	game->pos_ennemy++;
	if (game->sens_ennemy == 1)
		ennemy_droit(game);
	else if (game->sens_ennemy == 0)
		ennemy_gauche(game);
}
