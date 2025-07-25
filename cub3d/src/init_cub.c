/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:25:51 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 12:32:50 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

#ifdef BONUS

static int	init_cub2(t_cub *cub)
{
	if (!check_boundaries(cub->m_head))
		return (EXIT_FAILURE);
	if (get_player(cub->m_head, cub))
		return (EXIT_FAILURE);
	if (map_contain_illegal_chars(cub->m_head))
		return (EXIT_FAILURE);
	if (xpm_to_sprite(cub->no_texture) || xpm_to_sprite(cub->so_texture)
		|| xpm_to_sprite(cub->we_texture) || xpm_to_sprite(cub->ea_texture)
		|| xpm_to_sprite(cub->do_texture))
		return (EXIT_FAILURE);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (EXIT_FAILURE);
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	set_basic_windows_control(cub);
	cub->img = malloc(sizeof(t_cubimg));
	if (!cub->img)
		return (EXIT_FAILURE);
	cub->img->img = NULL;
	make_map(cub->m_head, cub);
	cub->rays = NULL;
	return (EXIT_SUCCESS);
}
#else

static int	init_cub2(t_cub *cub)
{
	if (!check_boundaries(cub->m_head))
		return (EXIT_FAILURE);
	if (get_player(cub->m_head, cub))
		return (EXIT_FAILURE);
	if (map_contain_illegal_chars(cub->m_head))
		return (EXIT_FAILURE);
	if (xpm_to_sprite(cub->no_texture) || xpm_to_sprite(cub->so_texture)
		|| xpm_to_sprite(cub->we_texture) || xpm_to_sprite(cub->ea_texture))
		return (EXIT_FAILURE);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (EXIT_FAILURE);
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	set_basic_windows_control(cub);
	cub->img = malloc(sizeof(t_cubimg));
	if (!cub->img)
		return (EXIT_FAILURE);
	cub->img->img = NULL;
	make_map(cub->m_head, cub);
	cub->rays = NULL;
	return (EXIT_SUCCESS);
}
#endif

int	init_cub(t_cub *cub, char*path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	if (fd < 0)
		return (EXIT_FAILURE);
	if (get_infos(cub, fd))
		return (bleed_fd(fd), EXIT_FAILURE);
	bleed_fd(fd);
	return (init_cub2(cub));
}
