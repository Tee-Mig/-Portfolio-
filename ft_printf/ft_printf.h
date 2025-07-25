/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:39:51 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/16 13:40:22 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

int		display_c(char c);
int		display_s(char *str);
int		display_d(int nb);
int		display_u(unsigned int nb);
int		display_x(unsigned int nb);
int		display_xx(unsigned int nb);
int		ft_printf(const char *str, ...);
int		nb_count(long n);
int		display_i(int nb);
int		print_flags(va_list args, int i, char *str);
int		ft_len_p(uintptr_t p);
int		display_p(unsigned long long ptr);

size_t	ft_strlen(const char *str);

void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);
void	ft_print_p(uintptr_t p);
void	process_hex(char *hex, int base_len, char *base_hex, unsigned int nb);

#endif