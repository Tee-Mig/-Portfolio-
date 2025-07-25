/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:15:38 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/02 13:09:00 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*strr;

	i = 0;
	strr = (char *)str;
	if (c == 0)
		return (strr + ft_strlen(strr));
	while (strr[i] != '\0')
	{
		if (strr[i] == (unsigned char)c)
			return (strr + i);
		i++;
	}
	return (NULL);
}
