/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 04:55:29 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 08:26:21 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

#ifdef BONUS

char	put_info(t_cub *cub, char **info)
{
	if (ft_strncmp(info[0], "NO", 3) == 0)
		return (get_texture(info[1], &cub->no_texture));
	else if (ft_strncmp(info[0], "SO", 3) == 0)
		return (get_texture(info[1], &cub->so_texture));
	else if (ft_strncmp(info[0], "WE", 3) == 0)
		return (get_texture(info[1], &cub->we_texture));
	else if (ft_strncmp(info[0], "EA", 3) == 0)
		return (get_texture(info[1], &cub->ea_texture));
	else if (ft_strncmp(info[0], "F", 2) == 0)
		return (get_color(&cub->floor_color, info[1]));
	else if (ft_strncmp(info[0], "C", 2) == 0)
		return (get_color(&cub->ceiling_color, info[1]));
	else if (ft_strncmp(info[0], "DO", 2) == 0)
		return (get_texture(info[1], &cub->do_texture));
	else
		return (1);
}

#else

char	put_info(t_cub *cub, char **info)
{
	if (ft_strncmp(info[0], "NO", 3) == 0)
		return (get_texture(info[1], &cub->no_texture));
	else if (ft_strncmp(info[0], "SO", 3) == 0)
		return (get_texture(info[1], &cub->so_texture));
	else if (ft_strncmp(info[0], "WE", 3) == 0)
		return (get_texture(info[1], &cub->we_texture));
	else if (ft_strncmp(info[0], "EA", 3) == 0)
		return (get_texture(info[1], &cub->ea_texture));
	else if (ft_strncmp(info[0], "F", 2) == 0)
		return (get_color(&cub->floor_color, info[1]));
	else if (ft_strncmp(info[0], "C", 2) == 0)
		return (get_color(&cub->ceiling_color, info[1]));
	else
		return (1);
}

#endif

void	place_map_at_end(t_cub *cub, t_map *to_place)
{
	t_map	*m;

	to_place->next = NULL;
	if (cub->m_head == NULL)
	{
		to_place->prev = NULL;
		cub->m_head = to_place;
		return ;
	}
	m = cub->m_head;
	while (m->next)
		m = m->next;
	m->next = to_place;
	to_place->prev = m;
}
