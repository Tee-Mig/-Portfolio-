/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:11:38 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/16 13:35:04 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	display_c(char c)
{
	ft_putchar(c);
	return (1);
}

int	display_s(char *str)
{
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	ft_putstr(str);
	return (ft_strlen(str));
}

int	display_d(int nb)
{
	ft_putnbr(nb);
	return (nb_count(nb));
}

int	display_u(unsigned int nb)
{
	char	*base_dix;
	int		base_len;
	char	*dix;
	int		base_l;

	base_dix = "0123456789";
	base_len = nb_count(nb);
	base_l = base_len;
	dix = malloc(sizeof(char) * (base_len + 1));
	if (!dix)
		return (0);
	dix[base_len] = '\0';
	while (--base_len >= 0)
	{
		dix[base_len] = base_dix[nb % 10];
		nb /= 10;
	}
	ft_putstr(dix);
	free(dix);
	return (base_l);
}

int	display_x(unsigned int nb)
{
	int				base_len;
	char			*hex;
	unsigned int	n;
	char			*base_hex;
	int				base_l;

	n = nb;
	base_len = 1;
	while (n >= 16)
	{
		base_len++;
		n /= 16;
	}
	base_l = base_len;
	base_hex = "0123456789abcdef";
	hex = malloc(sizeof(char) * (base_len + 1));
	if (!hex)
		return (0);
	process_hex(hex, base_len, base_hex, nb);
	free(hex);
	return (base_l);
}
