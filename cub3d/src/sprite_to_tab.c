/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 02:34:31 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 08:49:02 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static char	***get_colors2(char ***colors, int fd, int x, t_sprite *sprite)
{
	int		i;
	char	*s;
	char	*tmp;

	i = -1;
	while (++i < x)
	{
		colors[i] = malloc(sizeof(char **) * 3);
		if (colors[i] == NULL)
			return (free_split(*colors), free(colors), NULL);
		s = get_next_line(fd);
		if (s == NULL)
			return (free_split(*colors), free(colors), NULL);
		colors[i][0] = ft_substr(s, 1, sprite->char_per_pixel);
		tmp = ft_substr(s, sprite->char_per_pixel + 3, ft_strlen(s));
		colors[i][1] = ft_strtrim(tmp, " \",\n");
		colors[i][2] = NULL;
		free(tmp);
		free(s);
	}
	colors[i] = NULL;
	return (colors);
}

static int	get_sprite_info(t_sprite	*sprite, int fd)
{
	char	*s;
	char	*s2;
	int		rv;

	s = get_next_line(fd);
	s2 = ft_strtrim(s, "'\"");
	free(s);
	s = s2;
	sprite->width = ft_atoi(s);
	s2 = ft_strchr(s, ' ');
	sprite->height = ft_atoi(s2);
	s2 = ft_strchr(++s2, ' ');
	rv = ft_atoi(s2);
	s2 = ft_strchr(++s2, ' ');
	sprite->char_per_pixel = ft_atoi(s2);
	free(s);
	if (sprite->width < 1 || sprite->height < 1
		|| rv < 1 || sprite->char_per_pixel < 1)
		return (-1);
	return (rv);
}

static char	***get_colors(char ***colors, int fd, t_sprite *sprite)
{
	int		x;

	x = get_sprite_info(sprite, fd);
	if (x == -1)
		return (NULL);
	colors = malloc(sizeof(char **) * (x + 1));
	if (colors == NULL)
		return (NULL);
	return (get_colors2(colors, fd, x, sprite));
}

int	xpm_to_sprite(t_sprite *sprite)
{
	char	*s;
	int		fd;
	char	***colors;

	colors = NULL;
	fd = open(sprite->path, O_RDONLY);
	if (fd == -1)
		return (1);
	s = get_next_line(fd);
	while (ft_strncmp("/* columns rows colors chars-per-pixel */\n", s,
			ft_strlen(s)) != 0)
	{
		free(s);
		s = get_next_line(fd);
		if (s == NULL)
			return (1);
	}
	colors = get_colors(colors, fd, sprite);
	if (colors == NULL)
		return (free(s), 1);
	sprite->img = get_image(colors, fd, sprite);
	return (free(s), bleed_fd(fd), free_colors(colors), 0);
}
