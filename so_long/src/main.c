/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:16:51 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 16:21:28 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_arg(char *input)
{
	int	i;

	if (!input)
		return (0);
	i = 0;
	while (input[i])
		i++;
	i -= 1;
	if (input[i] == 'r' && input[i - 1] == 'e'
		&& input[i - 2] == 'b' && input[i - 3] == '.')
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2)
	{
		game.map = read_map(av[1]);
		if (check_arg(av[1]) && check_map(&game))
		{
			init_game(&game);
			play(&game);
		}
		else
		{
			ft_putstr
			("Erreur, il y a un probleme avec ton argument ou ta map.\n");
			if (game.map)
				free_map(game.map);
			exit(1);
		}
	}
	else
	{
		ft_putstr("Erreur, il y a un problème avec ton nombre argument.\n");
		exit(1);
	}
}
