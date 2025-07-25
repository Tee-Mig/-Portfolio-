/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:59:39 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/01 18:57:20 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_d;

	i = 0;
	if (!dst || !src)
		return (0);
	len_d = ft_strlen(dst);
	if (size <= len_d || size == 0)
		return (size + ft_strlen(src));
	while (src[i] && len_d < (size - 1))
	{
		dst[len_d] = src[i];
		i++;
		len_d++;
	}
	dst[len_d] = '\0';
	while (src[i])
	{
		i++;
		len_d++;
	}
	return (len_d);
}
