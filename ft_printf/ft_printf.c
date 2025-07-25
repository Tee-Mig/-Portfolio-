/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:57:49 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/16 13:20:44 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_flags(va_list args, int i, char *str)
{
	int	char_count;

	char_count = 0;
	if (str[i] == 'c')
		char_count += display_c(va_arg(args, int));
	if (str[i] == 's')
		char_count += display_s(va_arg(args, char *));
	if (str[i] == 'd')
		char_count += display_d(va_arg(args, int));
	if (str[i] == 'i')
		char_count += display_i(va_arg(args, int));
	if (str[i] == 'u')
		char_count += display_u(va_arg(args, unsigned int));
	if (str[i] == 'x')
		char_count += display_x(va_arg(args, unsigned int));
	if (str[i] == 'X')
		char_count += display_xx(va_arg(args, unsigned int));
	if (str[i] == 'p')
		char_count += display_p(va_arg(args, unsigned long int));
	if (str[i] == '%')
	{
		ft_putchar('%');
		char_count++;
	}
	return (char_count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		char_count;

	char_count = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			char_count += print_flags(args, i, (char *)str);
		}
		else
		{
			ft_putchar(str[i]);
			char_count++;
		}
		i++;
	}
	va_end(args);
	return (char_count);
}
