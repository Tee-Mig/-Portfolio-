/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:32:58 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/14 04:34:10 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

char	*move_to_junk(char *tmp, char *junk)
{
	char	*njunk;

	if (!(junk == NULL || junk == 0))
	{
		njunk = malloc(BUFFER_SIZE + 1 + ft_strlen(junk));
		if (njunk == NULL)
		{
			free(junk);
			return (NULL);
		}
		ft_strlcpy(njunk, junk, ft_strlen(junk) + 1);
		ft_strlcat(njunk, tmp, BUFFER_SIZE + ft_strlen(junk) + 1);
	}
	else
	{
		njunk = malloc(BUFFER_SIZE + 1);
		if (njunk == NULL)
		{
			free(junk);
			return (NULL);
		}
		ft_strlcpy(njunk, tmp, BUFFER_SIZE + 1);
	}
	free(junk);
	return (njunk);
}

char	*get_line_from_junk(char *junk)
{
	char	*v;
	size_t	i;
	size_t	size;

	i = 0;
	if (junk[0] == 0)
		return (NULL);
	while (*(junk + i) != '\n' && *(junk + i))
		i++;
	size = i + 1;
	v = malloc(size + 1);
	if (v == NULL)
		return (NULL);
	ft_strlcpy(v, junk, size + 1);
	return (v);
}

int	is_line_in_junk(char *junk)
{
	size_t	i;

	i = 0;
	if (junk == NULL || junk == 0)
		return (0);
	while (junk[i] != 0)
	{
		if (junk[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_line_from_junk(char *junk)
{
	size_t	new_size;
	char	*new_junk;
	size_t	size;

	size = 0;
	while (*(junk + size) != '\n' && *(junk + size))
		size++;
	new_size = ft_strlen(junk) - size + 1;
	new_junk = malloc(new_size + 1);
	if (new_junk == NULL)
	{
		free(junk);
		return (NULL);
	}
	ft_strlcpy(new_junk, junk + size + 1, new_size + 1);
	free(junk);
	return (new_junk);
}

char	*get_next_line(int fd)
{
	char		*v;
	static char	*junk;
	ssize_t		r;

	while (!is_line_in_junk(junk))
	{
		v = malloc(BUFFER_SIZE + 1);
		if (v == NULL)
			return (NULL);
		ft_bzero(v, BUFFER_SIZE + 1);
		r = read(fd, v, BUFFER_SIZE);
		if (!r || r == -1)
		{
			v = ft_end(junk, v);
			free(junk);
			junk = NULL;
			return (v);
		}
		junk = move_to_junk(v, junk);
		free(v);
	}
	v = get_line_from_junk(junk);
	junk = remove_line_from_junk(junk);
	return (v);
}
