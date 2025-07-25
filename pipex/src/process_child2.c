/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:57:18 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 13:57:40 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_child2(t_pipex *pipex, char **envp, char **av)
{
	pipex->fd2 = open(av[4], O_RDWR | O_TRUNC);
	if (pipex->fd2 == -1)
	{
		ft_putstr("Error: open\n");
		second_error_child2(pipex);
		close(pipex->fd1);
		return (0);
	}
	pipex->id2 = fork();
	if (pipex->id2 == -1)
	{
		perror("Error");
		second_error_child2(pipex);
		return (0);
	}
	if (pipex->id2 == 0)
	{
		if (process2_child2(pipex, envp) == 0)
			return (0);
	}
	return (1);
}

int	process2_child2(t_pipex *pipex, char **envp)
{
	if (close(pipex->pipefd[1]) == -1)
	{
		perror("Error");
		error_child2(pipex);
		return (0);
	}
	if (dup2(pipex->pipefd[0], 0) == -1)
	{
		perror("Error");
		error_child2(pipex);
		return (0);
	}
	if (dup2(pipex->fd2, 1) == -1)
	{
		perror("Error");
		error_child2(pipex);
		return (0);
	}
	exec_command2(pipex, envp);
	return (1);
}

void	exec_command2(t_pipex *pipex, char **envp)
{
	if (pipex->nb_arg_3 != 0)
	{
		if (!access(pipex->commands2[0], 0))
		{
			if (execve(pipex->commands2[0], pipex->commands2, envp) == -1)
				perror("error excve: ");
		}
		pipex->i = -1;
		while (pipex->pathcp[++pipex->i])
		{
			pipex->pathcp[pipex->i] = ft_strjoin(pipex->pathcp[pipex->i],
					pipex->commands2[0]);
			if (!access(pipex->pathcp[pipex->i], 0))
			{
				pipex->commands2[0] = pipex->pathcp[pipex->i];
				if (execve(pipex->commands2[0], pipex->commands2, envp) == -1)
					perror("error excve: ");
			}
		}
	}
	write(2, "Error: command not found\n", 25);
	error_child2(pipex);
	exit(1);
}

void	error_child2(t_pipex *pipex)
{
	free_tab(pipex->commands1);
	free_tab(pipex->commands2);
	free_tab(pipex->path);
	free_tab(pipex->pathcp);
	close(pipex->fd1);
	close(pipex->fd2);
	close(pipex->pipefd[0]);
}

void	second_error_child2(t_pipex *pipex)
{
	free_tab(pipex->commands1);
	free_tab(pipex->commands2);
	free_tab(pipex->path);
	free_tab(pipex->pathcp);
	close(pipex->fd1);
}
