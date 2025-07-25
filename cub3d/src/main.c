/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:56:17 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 12:28:38 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"
#include <string.h>

float	distance_between_points(t_point *point_a, t_point *point_b)
{
	float	dx;
	float	dy;

	dx = point_b->x - point_a->x;
	dy = point_b->y - point_a->y;
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

static void	change_ray_info(t_ray *ray, t_wall *w, t_player *p, t_point **rv)
{
	float	dist;
	t_point	*point;

	point = does_intersect(p, ray, w);
	if (!point)
		return ;
	dist = distance_between_points(p->pos, point);
	if (!*rv || dist < ray->distance)
	{
		ray->distance = dist;
		ray->wall = w;
		if (*rv)
			free(*rv);
		*rv = point;
		w = w->next;
		return ;
	}
	free(point);
}

t_point	*closest_intersection(t_player *player, t_ray *ray, t_wall *head)
{
	t_point	*rv;
	t_wall	*w;

	rv = NULL;
	w = head;
	while (w)
	{
		change_ray_info(ray, w, player, &rv);
		w = w->next;
	}
	return (rv);
}

#ifdef BONUS

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
	{
		printf("Usage: ./cub3d path/to/map.cub");
		return (1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4,
			".cub", 5) != 0)
	{
		printf("Invalid file extension");
		return (1);
	}
	cub = malloc(sizeof(t_cub));
	bzero(cub, sizeof(t_cub));
	if (init_cub(cub, av[1]))
		return (free_cub(cub), printf("Error\n"), 1);
	XFixesHideCursor(cub->mlx->display, cub->mlx_win->window);
	mlx_mouse_move(cub->mlx, cub->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(cub->mlx, draw, cub);
	mlx_loop(cub->mlx);
	free_cub(cub);
	return (0);
}

#else

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
	{
		printf("Usage: ./cub3d path/to/map.cub");
		return (1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4,
			".cub", 5) != 0)
	{
		printf("Invalid file extension");
		return (1);
	}
	cub = malloc(sizeof(t_cub));
	bzero(cub, sizeof(t_cub));
	if (init_cub(cub, av[1]))
		return (free_cub(cub), printf("Error\n"), 1);
	mlx_loop_hook(cub->mlx, draw, cub);
	mlx_loop(cub->mlx);
	free_cub(cub);
	return (0);
}

#endif
