/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:03:15 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 15:44:30 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map(char *input)
{
	int		fd;
	char	**map;
	char	*save;
	char	*line;

	fd = open(input, O_RDWR);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (NULL);
	}
	save = ft_strdup("");
	while (line)
	{
		save = ft_strjoin(save, line);
		free(line);
		line = get_next_line(fd);
	}
	map = ft_split(save, '\n');
	free(save);
	close(fd);
	return (map);
}
