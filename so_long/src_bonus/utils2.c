/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:39:55 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 15:18:37 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

char	*get_next_line(int fd)
{
	char	buff[2];
	char	*str;
	int		len;

	str = ft_strdup("");
	len = 1;
	while (ft_verif_n(str) == 0 && len != 0)
	{
		len = read(fd, buff, 1);
		if (len == -1)
			return (NULL);
		if (len != 0)
		{
			buff[1] = '\0';
			str = ft_strjoin(str, buff);
		}
	}
	if (!str[0])
	{
		free(str);
		return (NULL);
	}
	return (str);
}

void	ft_putchar(char c)
{
	int	x;

	(void)x;
	x = write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	x;

	(void)x;
	x = write(1, str, ft_strlen(str));
}

void	ft_putnbr(int nb)
{
	unsigned int	n;

	if (nb < 0)
	{
		ft_putchar('-');
		n = -nb;
	}
	else
		n = nb;
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		n %= 10;
	}
	ft_putchar(n + '0');
}
