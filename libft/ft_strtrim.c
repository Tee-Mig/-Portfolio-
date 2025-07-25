/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:05:47 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/11/25 18:05:47 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		len;
	int		j;

	j = -1;
	i = -1;
	str = (char *)s1;
	len = ft_strlen(s1);
	while (s1[len - 1] && ft_strchr(set, s1[len - 1]))
		len--;
	if (!len)
	{
		str = ft_strdup("");
		return (str);
	}
	while (s1[++i] && ft_strchr(set, s1[i]))
		len--;
	str = malloc(sizeof(char) * (len + 1));
	while (len > ++j)
		str[j] = s1[i++];
	str[j] = '\0';
	return (str);
}
