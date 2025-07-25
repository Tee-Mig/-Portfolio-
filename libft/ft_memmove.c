/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:34:02 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/01 14:02:57 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*destf;
	const unsigned char	*srcf;
	size_t				i;

	i = 0;
	destf = (unsigned char *)dest;
	srcf = (unsigned char *)src;
	if (destf > srcf)
	{
		while (n > i)
		{
			destf[n - i - 1] = srcf[n - i - 1];
			i++;
		}
	}
	else
	{
		while (n > i)
		{
			destf[i] = srcf[i];
			i++;
		}
	}
	return (dest);
}
