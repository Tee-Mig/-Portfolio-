/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 05:06:44 by ccambium          #+#    #+#             */
/*   Updated: 2021/10/30 05:06:44 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i))
	{
		if ((unsigned char)c == *(s + i))
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char)c == *(s + i))
		return ((char *)s + i);
	return (NULL);
}
