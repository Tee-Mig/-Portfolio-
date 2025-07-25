/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_contain_illegal_chars.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:18:18 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 13:56:20 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	between_ones(char *line, size_t x)
{
	if (x > 0 && x < ft_strlen(line) - 1)
		return ((line[x - 1] == '1' || is_space(line[x - 1]))
			&& (line[x + 1] == '1' || is_space(line[x + 1])));
	if (x == 0)
		return (line[x + 1] == '1' || is_space(line[x + 1]));
	if (x == ft_strlen(line) - 1)
		return (line[x - 1] == '1' || is_space(line[x - 1]));
	return (0);
}

#ifdef BONUS

int	map_contain_illegal_chars(t_map *head)
{
	size_t	i;
	t_map	*m;

	m = head;
	while (m)
	{
		i = -1;
		while (m->line[++i])
		{
			if (is_space(m->line[i]) && (between_ones(m->line, i)))
				continue ;
			if (m->line[i] != '1' && m->line[i] != '0' && m->line[i] != '2'
				&& m->line[i] != 'N' && m->line[i] != 'S' && m->line[i] != 'E'
				&& m->line[i] != 'W')
				return (1);
		}
		m = m->next;
	}
	return (0);
}
#else

int	map_contain_illegal_chars(t_map *head)
{
	size_t	i;
	t_map	*m;

	m = head;
	while (m)
	{
		i = -1;
		while (m->line[++i])
		{
			if (is_space(m->line[i]) && (between_ones(m->line, i)))
				continue ;
			if (m->line[i] != '1' && m->line[i] != '0' && m->line[i] != 'W'
				&& m->line[i] != 'N' && m->line[i] != 'S' && m->line[i] != 'E')
				return (1);
		}
		m = m->next;
	}
	return (0);
}
#endif
