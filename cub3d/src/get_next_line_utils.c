/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:28:53 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/14 04:33:42 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(dst + i) != 0 && i < size && size != 0)
		i++;
	while (*(src + j) != 0 && i < size - 1 && size != 0)
	{
		*(dst + i) = *(src + j);
		*(dst + i + 1) = 0;
		i++;
		j++;
	}
	while (*(src + j) != 0)
	{
		j++;
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*(src + i) != 0 && i < size - 1 && size != 0)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (size != 0)
		*(dst + i) = 0;
	while (*(src + i) != 0)
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)s + i) = 0;
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i) != 0)
		i++;
	return (i);
}

char	*ft_end(char *junk, char *v)
{
	free(v);
	v = NULL;
	if (!(junk == NULL || junk == 0))
		v = get_line_from_junk(junk);
	return (v);
}
