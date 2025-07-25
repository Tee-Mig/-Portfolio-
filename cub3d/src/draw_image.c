/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:38:13 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 12:32:50 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	draw_scene2(t_cub *cub, t_render *render, size_t i, size_t j)
{
	if (j < render->wallstart && cub->ceiling_color)
		ft_put_pixel(cub->img, i, j, cub->ceiling_color);
	else if (j >= render->wallstart && j <= render->wallend)
	{
		if (render->line_h == 0 || !cub->rays[i]->intersection)
			return (1);
		if (render->wally >= render->sprite->height)
			render->wally = (int)render->wally % render->sprite->height;
		ft_put_pixel(cub->img, i, j,
			render->sprite->img[(int)render->wally][(int)render->wallx]);
		render->wally += render->stepy;
	}
	else if (j > render->wallend && cub->floor_color)
		ft_put_pixel(cub->img, i, j, cub->floor_color);
	return (0);
}

void	draw_scene(t_cub *cub)
{
	size_t		i;
	size_t		j;
	t_render	render;

	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		cub->rays[i]->distance *= cos(cub->rays[i]->angle
				- cub->rays[WIDTH / 2]->angle);
		init_render(i, &render, cub);
		while (++j < HEIGHT)
		{
			if (draw_scene2(cub, &render, i, j))
				break ;
		}
	}
}

#ifdef BONUS

void	draw_crosshair(t_cubimg *img)
{
	t_point	a;
	t_point	b;

	a.x = WIDTH / 2 - 1;
	b.x = WIDTH / 2 + 1;
	a.y = HEIGHT / 2 - 1;
	b.y = HEIGHT / 2 - 1;
	draw_line(img, &a, &b, 0xFF00FF);
	a.y += 1;
	b.y += 1;
	draw_line(img, &a, &b, 0xFF00FF);
	a.y += 1;
	b.y += 1;
	draw_line(img, &a, &b, 0xFF00FF);
}

int	draw(t_cub *cub)
{
	void	*img_tmp;

	img_tmp = cub->img->img;
	mouse_loop(cub);
	move_doors(cub->w_head);
	cub->img->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	init_rays(cub);
	draw_scene(cub);
	draw_minimap(cub);
	draw_crosshair(cub->img);
	mlx_clear_window(cub->mlx, cub->mlx_win);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img, 0, 0);
	if (img_tmp != NULL)
		mlx_destroy_image(cub->mlx, img_tmp);
	return (0);
}
#else

int	draw(t_cub *cub)
{
	void	*img_tmp;

	img_tmp = cub->img->img;
	cub->img->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	init_rays(cub);
	draw_scene(cub);
	mlx_clear_window(cub->mlx, cub->mlx_win);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img, 0, 0);
	if (img_tmp != NULL)
		mlx_destroy_image(cub->mlx, img_tmp);
	return (0);
}
#endif
