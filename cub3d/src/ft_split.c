/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 06:31:06 by ccambium          #+#    #+#             */
/*   Updated: 2021/11/05 06:31:06 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static size_t	count_world(char const *s, char c)
{
	size_t	v;
	size_t	i;
	int		flag;

	flag = 1;
	v = 0;
	i = 0;
	while (*(s + i) != 0)
	{
		if (*(s + i) == c)
			flag = 1;
		else if (*(s + i) != c && flag == 1)
		{
			flag = 0;
			v++;
		}
		i++;
	}
	return (v);
}

static size_t	size_next_word(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) != 0 && *(s + i) != c)
		i++;
	return (i);
}

static void	*s_free_all(char **tab)
{
	size_t	i;
	void	*x;

	i = 0;
	while (tab[i] != NULL)
	{
		x = tab[i];
		i++;
		free(x);
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**v;
	size_t	len;
	size_t	wc;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	wc = count_world(s, c);
	v = malloc(sizeof(char *) * (wc + 1));
	if (v == NULL)
		return (NULL);
	while (++i < wc)
	{
		while (s[j] == c && s[j] != 0)
			j++;
		len = size_next_word(s + j, c);
		v[i] = malloc(len + 1);
		if (v[i] == NULL)
			return (s_free_all(v));
		ft_strlcpy(v[i], s + j, len + 1);
		j += len;
	}
	v[i] = NULL;
	return (v);
}
