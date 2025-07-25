/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:49:20 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 16:00:00 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	if_rectangle(char **input)
{
	int	i;
	int	len;

	if (!input[0])
		return (0);
	len = ft_strlen(input[0]);
	i = 0;
	while (input[++i])
	{
		if (ft_strlen(input[i]) != len)
			return (0);
	}
	return (1);
}

static int	if_wall_around(char **input)
{
	int	i;
	int	j;

	i = 0;
	while (input[0][i])
	{
		if (input[0][i] != '1')
			return (0);
		i++;
	}
	j = -1;
	while (input[++j])
	{
		if (input[j][0] != '1' || input[j][i - 1] != '1')
			return (0);
	}
	i = 0;
	while (input[0][i])
	{
		if (input[j - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	if_other_char(char **input)
{
	int	i;
	int	j;

	i = -1;
	while (input[++i])
	{
		j = -1;
		while (input[i][++j])
		{
			if (!(input[i][j] == '0' || input[i][j] == '1'
				|| input[i][j] == 'C' || input[i][j] == 'E'
				|| input[i][j] == 'E' || input[i][j] == 'P'
				|| input[i][j] == 'X'))
				return (0);
		}
	}
	return (1);
}

static int	check_number_each(t_game *game)
{
	int	i;
	int	j;

	game->nb_img_item = 0;
	game->nb_img_exit = 0;
	game->nb_img_start_character = 0;
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'C')
				game->nb_img_item++;
			else if (game->map[i][j] == 'E')
				game->nb_img_exit++;
			else if (game->map[i][j] == 'P')
				game->nb_img_start_character++;
		}
	}
	if (game->nb_img_item == 0 || game->nb_img_exit == 0
		|| game->nb_img_start_character != 1)
		return (0);
	return (1);
}

int	check_map(t_game *game)
{
	if (!game->map)
		return (0);
	if (!if_rectangle(game->map))
		return (0);
	if (!if_wall_around(game->map))
		return (0);
	if (!if_other_char(game->map))
		return (0);
	if (!check_number_each(game))
		return (0);
	return (1);
}
