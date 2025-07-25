/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_are_null.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:04:47 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 08:05:41 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

#ifdef BONUS

char	textures_are_null(t_cub *cub)
{
	if (cub->no_texture == NULL || cub->so_texture == NULL
		|| cub->we_texture == NULL || cub->ea_texture == NULL
		|| cub->floor_color == -1 || cub->ceiling_color == -1
		|| cub->do_texture == NULL)
		return (1);
	return (0);
}

#else

char	textures_are_null(t_cub *cub)
{
	if (cub->no_texture == NULL || cub->so_texture == NULL
		|| cub->we_texture == NULL || cub->ea_texture == NULL
		|| cub->floor_color == -1 || cub->ceiling_color == -1)
		return (1);
	return (0);
}
#endif
