/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:23:23 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/03 12:37:35 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	int		i;
	int		len;
	int		j;

	j = -1;
	i = -1;
	str = (char *)s1;
	len = ft_strlen(s1);
	while (len > 0 && s1[len - 1] && ft_strchr(set, s1[len - 1]))
		len--;
	if (!len)
	{
		str = ft_strdup("");
		free(s1);
		return (str);
	}
	while (s1[++i] && ft_strchr(set, s1[i]))
		len--;
	str = malloc(sizeof(char) * (len + 1));
	while (len > ++j)
		str[j] = s1[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}

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

int	is_delimiter(char str)
{
	if (str == '|' || str == '<' || str == '>')
		return (1);
	return (0);
}

int	is_delimiter_str(char *str)
{
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}
