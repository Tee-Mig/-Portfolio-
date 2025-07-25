/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:55:16 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 12:32:50 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	draw_line(t_cubimg *img, t_point *start, t_point *end, int color)
{
	double	delatx;
	double	deltay;
	double	pixelx;
	double	pixely;
	int		pixels;

	delatx = end->x - start->x;
	deltay = end->y - start->y;
	pixels = sqrt((delatx * delatx) + (deltay * deltay));
	delatx /= pixels;
	deltay /= pixels;
	pixelx = start->x;
	pixely = start->y;
	while (pixels)
	{
		ft_put_pixel(img, pixelx, pixely, color);
		pixelx += delatx;
		pixely += deltay;
		--pixels;
	}
}
