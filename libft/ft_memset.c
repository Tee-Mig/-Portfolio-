/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:29:21 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/01 14:03:00 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*dest;
	int				i;

	i = 0;
	dest = str;
	while (n > 0)
	{
		dest[i] = (unsigned char) c;
		i++;
		n--;
	}
	return (str);
}
