/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:18:46 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/16 13:38:21 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	process_hex(char *hex, int base_len, char *base_hex, unsigned int nb)
{
	hex[base_len] = '\0';
	while (--base_len >= 0)
	{
		hex[base_len] = base_hex[nb % 16];
		nb /= 16;
	}
	ft_putstr(hex);
}
