/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:37:43 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 11:06:22 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verif_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	char	buff[2];
	char	*str;
	int		len;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	len = 1;
	while (ft_verif_n(str) == 0 && len != 0)
	{
		len = read(fd, buff, 1);
		if (len == -1)
			return (NULL);
		if (len != 0)
		{
			buff[1] = '\0';
			str = ft_strjoin_gnl(str, buff);
		}
	}
	if (!str[0])
	{
		free(str);
		return (NULL);
	}
	return (str);
}
