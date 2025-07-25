/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:05:51 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 15:01:47 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	word_count(char const *s, char c)
{
	int	tmp;
	int	wc;
	int	i;

	tmp = 1;
	wc = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && tmp == 1)
		{
			wc++;
			tmp = 0;
		}
		else if (s[i] == c && tmp == 0)
			tmp = 1;
		i++;
	}
	return (wc);
}

static char	*put_word(char const *s, char c, int *index)
{
	int		i;
	int		j;
	int		wc;
	char	*word;

	i = 0;
	j = 0;
	while (s[i] == c)
		i++;
	wc = i;
	while (s[wc] != c && s[wc])
		wc++;
	word = malloc(sizeof(char) * (wc - i + 1));
	if (!word)
		return (NULL);
	while (wc > i + j)
	{
		word[j] = s[i + j];
		j++;
	}
	word[j] = '\0';
	*index += wc;
	return (word);
}

char	**ft_split(char *s, char c)
{
	int		wc;
	int		i;
	int		index;
	char	**tab;

	i = 0;
	wc = word_count(s, c);
	index = 0;
	tab = malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		return (NULL);
	while (wc > i)
	{
		tab[i] = put_word(s + index, c, &index);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
