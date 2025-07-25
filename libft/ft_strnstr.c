/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:13:15 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/11/25 12:13:15 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;
	char	*str2;

	str2 = (char *)str;
	i = 0;
	if (to_find[0] == '\0')
		return (str2);
	while (str[i] && n > i)
	{
		j = 0;
		while (str[i + j] == to_find[j] && (i + j) < n)
		{
			j++;
			if (to_find[j] == '\0')
				return (str2 + i);
		}
		i++;
	}
	return (NULL);
}
