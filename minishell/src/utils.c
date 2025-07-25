/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:41:03 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/31 11:24:37 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(void *s1, void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	if (str1 && str2)
	{
		while (i < (n - 1) && (str1[i] || str2[i]) && (str1[i] == str2[i]))
		i++;
		return (str1[i] - str2[i]);
	}
	return (0);
}

char	*ft_strjoin(char *s1, char s2)
{
	size_t	ls1;
	size_t	i;
	char	*str;

	i = -1;
	ls1 = ft_strlen(s1);
	str = malloc(sizeof(char) * (ls1 + 2));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = s2;
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strjoin_str(char *s1, char *s2)
{
	size_t	ls1;
	size_t	ls2;
	size_t	i;
	size_t	j;
	char	*str;

	i = -1;
	j = 0;
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *s)
{
	char	*d;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	d = malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
