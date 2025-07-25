/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:48:01 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 08:37:24 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

#ifdef BONUS

t_wall	*create_wall(t_point *start, t_point *end,
	t_direction direction, t_walltypes type)
{
	t_wall	*rv;

	rv = malloc(sizeof(t_wall));
	if (!rv)
		return (NULL);
	rv->start = start;
	rv->end = end;
	rv->direction = direction;
	rv->type = type;
	rv->next = NULL;
	rv->state = closed;
	rv->offsetx = 0;
	rv->offsety = 0;
	return (rv);
}
#else

t_wall	*create_wall(t_point *start, t_point *end,
	t_direction direction, t_walltypes type)
{
	t_wall	*rv;

	rv = malloc(sizeof(t_wall));
	if (!rv)
		return (NULL);
	rv->start = start;
	rv->end = end;
	rv->direction = direction;
	rv->type = type;
	rv->next = NULL;
	return (rv);
}

#endif

t_point	*create_point(int x, int y)
{
	t_point	*rv;

	rv = malloc(sizeof(t_point));
	if (!rv)
		return (NULL);
	rv->x = x;
	rv->y = y;
	return (rv);
}

void	create_player(t_cub *cub, t_map *map, int x)
{
	cub->player = malloc(sizeof(t_player));
	if (cub->player == NULL)
		return ;
	cub->player->pos = malloc(sizeof(t_point));
	cub->player->pos->x = x * TILE + (TILE / 2);
	cub->player->pos->y = map->y * TILE + (TILE / 2);
	if (map->line[x] == 'N')
		cub->player->angle = 270;
	else if (map->line[x] == 'S')
		cub->player->angle = 90;
	else if (map->line[x] == 'E')
		cub->player->angle = 0;
	else if (map->line[x] == 'W')
		cub->player->angle = 180;
}
