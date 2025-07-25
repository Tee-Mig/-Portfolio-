/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_to_tab2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:48:46 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 12:32:50 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	get_cubimg2(char ***colors, char *s, t_sprite *sprite, size_t i)
{
	size_t	j;
	size_t	k;
	char	*x;

	j = -1;
	k = 1;
	while (k <= sprite->width * sprite->char_per_pixel)
	{
		x = ft_substr(s, k, sprite->char_per_pixel);
		if (!x)
			return (1);
		sprite->img[i][++j] = get_color_by_char(colors, x, sprite);
		free(x);
		k += sprite->char_per_pixel;
	}
	return (0);
}

int	**get_image(char ***colors, int fd, t_sprite *sprite)
{
	size_t	i;
	char	*s;

	s = get_next_line(fd);
	if (ft_strncmp("/* pixels */\n", s, ft_strlen(s)) != 0)
		return (free(s), NULL);
	free(s);
	i = -1;
	sprite->img = malloc(sizeof(int *) * (sprite->height + 1));
	if (sprite->img == NULL)
		return (sprite->img);
	while (++i < sprite->height)
	{
		s = get_next_line(fd);
		sprite->img[i] = malloc(sizeof(int) * sprite->width);
		if (!sprite->img[i] || get_cubimg2(colors, s, sprite, i))
			return (free_int_split(sprite->img), free(s), NULL);
		free(s);
	}
	sprite->img[i] = NULL;
	return (sprite->img);
}
