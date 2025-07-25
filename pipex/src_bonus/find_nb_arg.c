/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_nb_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:00:18 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/16 21:07:49 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	full_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i] == ' ')
		;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

int	find_nb_arg(char *str)
{
	int	i;
	int	nb_arg;

	if (!str[0] || full_space(str))
		return (0);
	nb_arg = 1;
	i = -1;
	while (str[++i] == ' ')
		;
	while (str[++i])
	{
		if (str[i] == ' ' && str[i - 1] != ' ')
			nb_arg++;
	}
	if (str[i - 1] == ' ')
		nb_arg--;
	return (nb_arg);
}
