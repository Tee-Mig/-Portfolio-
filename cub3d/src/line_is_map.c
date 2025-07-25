/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_is_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:07:38 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 14:42:30 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

#ifdef BONUS

char	line_is_map(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	if (line_is_spaces(line))
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!is_space(line[i]) && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != '2')
			return (0);
		i++;
	}
	return (1);
}
#else

char	line_is_map(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	if (line_is_spaces(line))
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!is_space(line[i]) && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}
#endif
