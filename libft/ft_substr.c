/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:39:17 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/14 12:32:28 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	else if (ft_strlen(s) < len)
		len = ft_strlen(s);
	else if (ft_strlen(s) == len)
		len -= start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i] != '\0')
	{
		if (len > j && start <= i)
		{
			str[j] = s[i];
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}
