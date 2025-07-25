/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 09:19:30 by ccambium          #+#    #+#             */
/*   Updated: 2021/11/01 09:19:30 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"
#include <stdio.h>
#include <string.h>

static int	is_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (*(set + i) != 0)
	{
		if ((unsigned char)c == *((unsigned char *)set + i))
			return (1);
		i++;
	}
	return (0);
}

static size_t	newsize(const char *s, char const *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s) + 1;
	i = 0;
	while ((*(s + i)) != 0 && is_in_set(*(s + i), set))
	{
		i++;
		len--;
	}
	i = ft_strlen(s) - 1;
	while (i < ft_strlen(s) && is_in_set(*(s + i), set))
	{
		i--;
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*v;

	len = newsize(s1, set);
	if (len == 0 || len > ft_strlen(s1) + 1)
	{
		v = malloc(1);
		v[0] = '\0';
		return (v);
	}
	v = malloc(len);
	if (v == NULL)
		return (NULL);
	i = 0;
	while (*(s1 + i) != 0 && is_in_set(*(s1 + i), set))
		i++;
	ft_strlcpy(v, ((const char *)s1 + i), len);
	return (v);
}
