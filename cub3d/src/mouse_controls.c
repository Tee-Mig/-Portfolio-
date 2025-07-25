/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:52:43 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/26 11:53:07 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

#ifdef BONUS

int	mouse_loop(t_cub *cub)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(cub->mlx, cub->mlx_win, &x, &y);
	mlx_mouse_move(cub->mlx, cub->mlx_win, WIDTH / 2, HEIGHT / 2);
	if (x != WIDTH / 2 || y != HEIGHT / 2)
		cub->player->angle += (x - WIDTH / 2) / 10;
	return (0);
}
#endif
