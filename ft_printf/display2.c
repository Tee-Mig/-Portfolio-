/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:53:43 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/16 13:45:08 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	display_xx(unsigned int nb)
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
	base_hex = "0123456789ABCDEF";
	hex = malloc(sizeof(char) * (base_len + 1));
	if (!hex)
		return (0);
	process_hex(hex, base_len, base_hex, nb);
	free(hex);
	return (base_l);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_len_p(uintptr_t p)
{
	int	len;

	len = 0;
	while (p != 0)
	{
		len++;
		p = p / 16;
	}
	return (len);
}

void	ft_print_p(uintptr_t p)
{
	if (p >= 16)
	{
		ft_print_p(p / 16);
		ft_print_p(p % 16);
	}
	else
	{
		if (p <= 9)
			ft_putchar_fd((p + '0'), 1);
		else
			ft_putchar_fd((p - 10 + 'a'), 1);
	}
}

int	display_p(unsigned long long ptr)
{
	int	len;

	len = 2;
	if (ptr == 0)
	{
		ft_putstr("0x0");
		return (3);
	}
	else
	{
		ft_putstr("0x");
		ft_print_p(ptr);
		len += ft_len_p(ptr);
	}
	return (len);
}
