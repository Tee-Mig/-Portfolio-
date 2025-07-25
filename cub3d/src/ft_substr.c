/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 09:41:47 by ccambium          #+#    #+#             */
/*   Updated: 2021/10/31 09:41:47 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			slen;
	char			*v;

	slen = ft_strlen(s) + 1;
	if (start > slen)
	{
		v = malloc(1);
		if (!v)
			return (NULL);
		*v = '\0';
		return (v);
	}
	if (len > slen - start)
		len = slen - start;
	v = malloc(len + 1);
	if (v == NULL)
		return (NULL);
	ft_strlcpy(v, s + start, len + 1);
	return (v);
}
