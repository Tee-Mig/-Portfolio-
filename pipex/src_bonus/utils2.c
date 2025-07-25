/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:03:46 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 16:40:24 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i] + 10);
}

void	close_fds(t_pipex *pipex)
{
	if (pipex->fd_output != -1)
		close(pipex->fd_output);
	if (pipex->fd_input != -1)
		close(pipex->fd_input);
}

void	close_pipes(t_pipex *pipex)
{
	pipex->i = -1;
	while (++pipex->i < pipex->nb_command - 1)
	{
		close(pipex->pipefd[pipex->i][0]);
		close(pipex->pipefd[pipex->i][1]);
		free(pipex->pipefd[pipex->i]);
	}
}
