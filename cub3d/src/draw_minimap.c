/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:59:26 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 12:32:50 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	set_background(t_cub *cub)
{
	t_point	a;
	t_point	b;
	size_t	i;

	i = -1;
	a.x = 0;
	b.x = WIDTH / 10;
	while (++i < HEIGHT / 10)
	{
		a.y = i;
		b.y = i;
		draw_line(cub->img, &a, &b, 0);
	}
}

void	draw_walls(t_cub *cub, t_minimap *mm)
{
	t_point	a;
	t_point	b;
	t_wall	*w;

	w = cub->w_head;
	while (w)
	{
		a.x = floor((w->start->x - mm->offsetx) / mm->xratio);
		a.y = floor((w->start->y - mm->offsety) / mm->yratio);
		b.x = floor((w->end->x - mm->offsetx) / mm->xratio);
		b.y = floor((w->end->y - mm->offsety) / mm->yratio);
		if (w->type != door)
			draw_line(cub->img, &a, &b, 0xFFFFFF);
		else if (w->state == opened)
			draw_line(cub->img, &a, &b, 0x00FF00);
		else if (w->state == closed)
			draw_line(cub->img, &a, &b, 0xFF0000);
		else
			draw_line(cub->img, &a, &b, 0x0000FF);
		w = w->next;
	}
}

void	add_player(t_cubimg *img, t_player *player, t_minimap *mm)
{
	t_point	a;
	t_point	b;

	a.x = floor((player->pos->x - mm->offsetx) / mm->xratio) - 1;
	b.x = ceil((player->pos->x - mm->offsetx) / mm->xratio) + 1;
	a.y = floor((player->pos->y - mm->offsety) / mm->yratio);
	b.y = ceil((player->pos->y - mm->offsety) / mm->yratio);
	draw_line(img, &a, &b, 0xFF00FF);
	a.y += 1;
	b.y += 1;
	draw_line(img, &a, &b, 0xFF00FF);
	a.y += 1;
	b.y += 1;
	draw_line(img, &a, &b, 0xFF00FF);
}

void	draw_minimap(t_cub *cub)
{
	t_minimap	mm;

	mm.xratio = get_xratio(cub->w_head);
	mm.yratio = get_yratio(cub->w_head);
	mm.offsetx = get_xoffset(cub->w_head);
	mm.offsety = get_yoffset(cub->w_head);
	set_background(cub);
	draw_walls(cub, &mm);
	add_player(cub->img, cub->player, &mm);
}
