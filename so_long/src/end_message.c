/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:13:44 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 16:21:13 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end_message(t_game *game)
{
	ft_putstr("Bien joué, tu as réussi a collecter tous les cristaux.");
	game->end = 1;
}
