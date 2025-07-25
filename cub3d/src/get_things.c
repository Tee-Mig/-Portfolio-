/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:18:29 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 14:24:17 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	get_texture(char *texture, t_sprite **sprite)
{
	if (*sprite)
		return (1);
	*sprite = malloc(sizeof(t_sprite));
	ft_bzero(*sprite, sizeof(t_sprite));
	(*sprite)->path = ft_strdup(texture);
	if ((*sprite)->path == NULL)
		return (1);
	if (ft_strncmp((*sprite)->path + ft_strlen((*sprite)->path) - 4,
			".xpm", 5) != 0)
		return (1);
	return (0);
}

int	get_color(int *x, char *s)
{
	char	**color;

	if (*x != -1)
		return (EXIT_FAILURE);
	color = ft_split(s, ',');
	if (count_char_tab(color) != 3)
		return (free_split(color), 1);
	if (check_colors(color))
		return (1);
	if (check_valid_rgb(color))
		return (free_split(color), 1);
	*x = ft_atoi(color[0]) << 16 | ft_atoi(color[1]) << 8 | ft_atoi(color[2]);
	free_split(color);
	return (0);
}

char	get_map(t_cub *cub, char *line, int fd)
{
	t_map	*m;
	size_t	i;

	while (line_is_spaces(line))
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (1);
	}
	i = -1;
	while (line)
	{
		if (!line_is_map(line))
			break ;
		m = malloc(sizeof(t_map));
		if (m == NULL)
			return (1);
		m->line = line;
		m->y = ++i;
		place_map_at_end(cub, m);
		line = get_next_line(fd);
	}
	return (free(line), bleed_fd(fd), EXIT_SUCCESS);
}

int	get_infos(t_cub	*cub, int fd)
{
	char	*line;
	char	**values;

	line = get_next_line(fd);
	while (line && !line_is_map(line))
	{
		if (line_is_spaces(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		values = ft_split_set(line, " \r\v\t\f\n");
		if (!values || !values[0] || !values[1] || put_info(cub, values))
			return (bleed_fd(fd), free_split(values), free(line), EXIT_FAILURE);
		free(line);
		free_split(values);
		line = get_next_line(fd);
	}
	if (textures_are_null(cub))
		return (free(line), bleed_fd(fd), EXIT_FAILURE);
	if (get_map(cub, line, fd))
		return (free(line), bleed_fd(fd), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	get_player(t_map *head, t_cub *cub)
{
	t_map	*m;
	size_t	i;

	m = head;
	while (m)
	{
		i = 0;
		while (m->line[i])
		{
			if (m->line[i] == 'N' || m->line[i] == 'S'
				|| m->line[i] == 'E' || m->line[i] == 'W')
			{
				if (cub->player)
					return (1);
				create_player(cub, m, i);
			}
			i ++;
		}
		m = m->next;
	}
	if (cub->player == NULL)
		return (1);
	return (0);
}
