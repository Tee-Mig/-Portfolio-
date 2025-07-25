/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonctions_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:31:28 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 15:35:04 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_path_env(t_pipex *pipex, char **envp)
{
	pipex->path = NULL;
	pipex->i = -1;
	while (envp[++pipex->i] && strncmp("PATH=", envp[pipex->i], 5) != 0)
		;
	if (!envp[pipex->i])
	{
		close_fds(pipex);
		ft_putstr("Error: path environment\n");
		return (0);
	}
	pipex->path = ft_split(envp[pipex->i] + 5, ':');
	if (!pipex->path)
	{
		ft_putstr("Error: malloc\n");
		close_fds(pipex);
		return (0);
	}
	if (add_end_path(pipex) == 0)
		return (0);
	return (1);
}

int	add_end_path(t_pipex *pipex)
{
	pipex->i = -1;
	while (pipex->path[++pipex->i])
		pipex->path[pipex->i] = ft_strjoin(pipex->path[pipex->i], "/");
	if (!pipex->path[0])
	{
		ft_putstr("Error: malloc\n");
		close_fds(pipex);
		free_tab(pipex->path);
		return (0);
	}
	return (1);
}

void	error1_pipe(t_pipex *pipex)
{
	ft_putstr("Error: malloc\n");
	while (--pipex->i >= 0)
	{
		close(pipex->pipefd[pipex->i][0]);
		close(pipex->pipefd[pipex->i][1]);
		free(pipex->pipefd[pipex->i]);
	}
	close_fds(pipex);
	free(pipex->pipefd);
	free(pipex->pid);
	free_tab(pipex->path);
}

void	error2_pipe(t_pipex *pipex)
{
	ft_putstr("Error: pipe\n");
	close(pipex->pipefd[pipex->i][0]);
	close(pipex->pipefd[pipex->i][1]);
	free(pipex->pipefd[pipex->i]);
	while (--pipex->i >= 0)
	{
		close(pipex->pipefd[pipex->i][0]);
		close(pipex->pipefd[pipex->i][1]);
		free(pipex->pipefd[pipex->i]);
	}
	close_fds(pipex);
	free(pipex->pipefd);
	free(pipex->pid);
	free_tab(pipex->path);
}

int	malloc_pipe(t_pipex *pipex)
{
	pipex->i = -1;
	while (++pipex->i < pipex->nb_command - 1)
	{
		pipex->pipefd[pipex->i] = malloc(sizeof(int) * 2);
		if (!pipex->pipefd[pipex->i])
		{
			error1_pipe(pipex);
			return (0);
		}
		if (pipe(pipex->pipefd[pipex->i]) == -1)
		{
			error2_pipe(pipex);
			return (0);
		}
	}
	return (1);
}
