/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:33:38 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/14 12:33:30 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destf;
	unsigned char	*srcf;
	int				i;

	i = 0;
	destf = dest;
	srcf = (unsigned char *)src;
	while (n > 0)
	{
		destf[i] = srcf[i];
		i++;
		n--;
	}
	return (dest);
}
