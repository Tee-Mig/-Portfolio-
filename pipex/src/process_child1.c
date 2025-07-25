/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:48:33 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 13:56:36 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_child1(t_pipex *pipex, char **envp)
{
	pipex->id1 = fork();
	if (pipex->id1 == -1)
	{
		ft_putstr("Error: fork\n");
		error_child1(pipex);
		return (0);
	}
	if (pipex->id1 == 0)
	{
		if (close(pipex->pipefd[0]) == -1)
			if (error_message(pipex) == 0)
				return (0);
		if (dup2(pipex->pipefd[1], 1) == -1)
			if (error_message(pipex) == 0)
				return (0);
		if (dup2(pipex->fd1, 0) == -1)
			if (error_message(pipex) == 0)
				return (0);
		exec_command1(pipex, envp);
	}
	return (1);
}

int	error_message(t_pipex *pipex)
{
	perror("Error");
	error_child1(pipex);
	return (0);
}

void	exec_command1(t_pipex *pipex, char **envp)
{
	if (pipex->nb_arg_2 != 0)
	{
		if (!access(pipex->commands1[0], 0))
		{
			if (execve(pipex->commands1[0], pipex->commands1, envp) == -1)
				perror("error excve: ");
		}
		pipex->i = -1;
		while (pipex->path[++pipex->i])
		{
			pipex->path[pipex->i] = ft_strjoin(pipex->path[pipex->i],
					pipex->commands1[0]);
			if (!access(pipex->path[pipex->i], 0))
			{
				pipex->commands1[0] = pipex->path[pipex->i];
				if (execve(pipex->commands1[0], pipex->commands1, envp) == -1)
					perror("error excve: ");
			}
		}
	}
	write(2, "Error: command not found\n", 25);
	error_child1(pipex);
	exit(1);
}

void	error_child1(t_pipex *pipex)
{
	free_tab(pipex->commands1);
	free_tab(pipex->commands2);
	free_tab(pipex->path);
	free_tab(pipex->pathcp);
	if (pipex->fd1 != -1)
		close(pipex->fd1);
	if (pipex->pipefd[1] != -1)
		close(pipex->pipefd[1]);
}
