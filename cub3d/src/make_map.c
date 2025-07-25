/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 06:15:15 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 07:48:56 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	add_end_wall(t_cub *cub, t_wall *wall)
{
	t_wall	*w;

	w = cub->w_head;
	wall ->next = NULL;
	if (!w)
	{
		cub->w_head = wall;
		return ;
	}
	while (w->next)
		w = w->next;
	w->next = wall;
}

void	add_walls(t_map *m, size_t x, size_t y, t_cub *cub)
{
	if (x > 0 && m->line[x - 1] != '1' && !is_space(m->line[x - 1]))
		add_end_wall(cub, create_wall(
				create_point(x * TILE, y * TILE),
				create_point(x * TILE, (y + 1) * TILE), east, wall));
	if (x + 1 < ft_strlen(m->line)
		&& m->line[x + 1] != '1' && !is_space(m->line[x + 1]))
		add_end_wall(cub, create_wall(
				create_point((x + 1) * TILE, y * TILE),
				create_point((x + 1) * TILE, (y + 1) * TILE), west, wall));
	if (m->next && x < ft_strlen(m->next->line)
		&& m->next->line[x] != '1' && !is_space(m->next->line[x]))
		add_end_wall(cub, create_wall(
				create_point(x * TILE, (y + 1) * TILE),
				create_point((x + 1) * TILE, (y + 1) * TILE), south, wall));
	if (m->prev && x < ft_strlen(m->prev->line)
		&& m->prev->line[x] != '1' && !is_space(m->prev->line[x]))
		add_end_wall(cub, create_wall(
				create_point(x * TILE, y * TILE),
				create_point((x + 1) * TILE, y * TILE), north, wall));
}

#ifdef BONUS

void	add_doors(t_map *m, size_t x, size_t y, t_cub *cub)
{
	if (x > 0 && m->line[x - 1] != '1'
		&& m->line[x - 1] != '2' && !is_space(m->line[x - 1]))
		add_end_wall(cub, create_wall(
				create_point(x * TILE, y * TILE),
				create_point(x * TILE, (y + 1) * TILE), east, door));
	if (x + 1 < ft_strlen(m->line) && m->line[x + 1] != '1'
		&& m->line[x + 1] != '2' && !is_space(m->line[x + 1]))
		add_end_wall(cub, create_wall(
				create_point((x + 1) * TILE, y * TILE),
				create_point((x + 1) * TILE, (y + 1) * TILE), west, door));
	if (m->next && x < ft_strlen(m->next->line) && m->next->line[x] != '1'
		&& m->line[x - 1] != '2' && !is_space(m->next->line[x]))
		add_end_wall(cub, create_wall(
				create_point(x * TILE, (y + 1) * TILE),
				create_point((x + 1) * TILE, (y + 1) * TILE), south, door));
	if (m->prev && x < ft_strlen(m->prev->line) && m->prev->line[x] != '1'
		&& m->line[x - 1] != '2' && !is_space(m->prev->line[x]))
		add_end_wall(cub, create_wall(
				create_point(x * TILE, y * TILE),
				create_point((x + 1) * TILE, y * TILE), north, door));
}

void	make_map(t_map *head, t_cub *cub)
{
	size_t	i;
	size_t	j;
	t_map	*m;

	j = 0;
	m = head;
	while (m)
	{
		i = 0;
		while (m->line[i])
		{
			if (m->line[i] == '1')
				add_walls(m, i, j, cub);
			if (m->line[i] == '2')
				add_doors(m, i, j, cub);
			i++;
		}
		j++;
		m = m->next;
	}
}
#else

void	make_map(t_map *head, t_cub *cub)
{
	size_t	i;
	size_t	j;
	t_map	*m;

	j = 0;
	m = head;
	while (m)
	{
		i = 0;
		while (m->line[i])
		{
			if (m->line[i] == '1')
				add_walls(m, i, j, cub);
			i++;
		}
		j++;
		m = m->next;
	}
}
#endif
