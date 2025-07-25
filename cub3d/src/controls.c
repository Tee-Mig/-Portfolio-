/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:28:11 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 10:22:25 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	look_left(t_cub *cub)
{
	cub->player->angle -= 2;
}

void	look_right(t_cub *cub)
{
	cub->player->angle += 2;
}

#ifdef	BONUS

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		move_forward(cub);
	if (keycode == KEY_S)
		move_backward(cub);
	if (keycode == KEY_A)
		move_left(cub);
	if (keycode == KEY_D)
		move_right(cub);
	if (keycode == KEY_ESC)
		mlx_loop_end(cub->mlx);
	if (keycode == KEY_LEFT)
		look_left(cub);
	if (keycode == KEY_RIGHT)
		look_right(cub);
	if (keycode == KEY_E)
		open_door(cub);
	return (0);
}
#else

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		move_forward(cub);
	if (keycode == KEY_S)
		move_backward(cub);
	if (keycode == KEY_A)
		move_left(cub);
	if (keycode == KEY_D)
		move_right(cub);
	if (keycode == KEY_ESC)
		mlx_loop_end(cub->mlx);
	if (keycode == KEY_LEFT)
		look_left(cub);
	if (keycode == KEY_RIGHT)
		look_right(cub);
	return (0);
}
#endif

void	set_basic_windows_control(t_cub *cub)
{
	mlx_hook(cub->mlx_win, 17, 0, mlx_loop_end, cub->mlx);
	mlx_hook(cub->mlx_win, 2, 1L << 0, key_press, cub);
}
