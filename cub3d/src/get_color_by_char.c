/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_by_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 04:43:48 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/18 04:21:24 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	value_x(char c)
{
	char	*s;
	char	*s2;
	int		i;

	i = 0;
	s = "0123456789ABCDEF";
	s2 = "0123456789abcdef";
	while (s[i])
	{
		if (s[i] == c || s2[i] == c)
			return (i);
		i++;
	}
	return (0);
}

static int	convert_h_x(char *hex, size_t max)
{
	if (max == 1)
		return (value_x(hex[-(max - ft_strlen(hex))]));
	return (ft_pow(16, max - 1) * value_x(hex[-(max - ft_strlen(hex))])
		+ convert_h_x(hex, max - 1));
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	hex_to_int(char *hex)
{
	int		x;
	char	*nhex;

	if (ft_strncmp(hex, "black", 5) == 0)
		return (0);
	nhex = ft_strtrim(hex, "x #");
	x = convert_h_x(nhex, ft_strlen(nhex));
	free(nhex);
	return (x);
}

int	get_color_by_char(char ***colors, char *c, t_sprite *sprite)
{
	size_t	i;

	i = 0;
	while (colors[i])
	{
		if (ft_strncmp(colors[i][0], c, sprite->char_per_pixel + 1) == 0)
			return (hex_to_int(colors[i][1]));
		i++;
	}
	free(c);
	return (0);
}
