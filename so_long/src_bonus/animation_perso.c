/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_perso.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:22:09 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 15:04:22 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	animation_perso(t_game *game)
{
	while (game->loop_anim_perso < 10000)
	{
		game->loop_anim_perso++;
		return ;
	}
	game->loop_anim_perso = 0;
	game->pos_perso++;
	if (game->sens_perso == 1)
		perso_droit(game);
	else if (game->sens_perso == 0)
		perso_gauche(game);
}
