/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:44:08 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/28 14:56:19 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	free_rays(t_ray	**rays)
{
	int	i;

	i = 0;
	if (rays == NULL)
		return ;
	while (i < WIDTH)
	{
		free(rays[i]->intersection);
		free(rays[i]);
		i++;
	}
	free(rays);
}

void	free_walls(t_wall *walls)
{
	t_wall	*w;
	t_wall	*ptr;

	w = walls;
	if (walls == NULL)
		return ;
	while (w)
	{
		ptr = w->next;
		free(w->end);
		free(w->start);
		free(w);
		w = ptr;
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_int_split(int **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_colors(char ***colors)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (colors == NULL)
		return ;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			free(colors[i][j]);
			j++;
		}
		free(colors[i]);
		i++;
	}
	free(colors);
}
