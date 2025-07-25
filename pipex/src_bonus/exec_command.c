/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:59:37 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 16:40:37 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_command(t_pipex *pipex, char **av, char **envp)
{
	char	*path_exec;

	pipex->commands = ft_split(av[pipex->begin_arg], ' ');
	pipex->nb_arg = find_nb_arg(av[pipex->begin_arg]);
	if (pipex->nb_arg != 0)
	{
		if (!access(pipex->commands[0], 0)
			&& pipex->nb_arg != 0)
		{
			if (execve(pipex->commands[0], pipex->commands, envp) == -1)
				perror("error excve");
		}
		pipex->i = -1;
		while (pipex->path[++pipex->i] && pipex->nb_arg != 0)
		{
			path_exec = ft_strjoin(pipex->path[pipex->i],
					pipex->commands[0]);
			execute_command(pipex, envp, path_exec);
			free(path_exec);
		}
	}
	if_command_not_found(pipex);
}

void	execute_command(t_pipex *pipex, char **envp, char *path_exec)
{
	if (!access(path_exec, 0))
	{
		pipex->commands[0] = path_exec;
		if (execve(pipex->commands[0], pipex->commands, envp) == -1)
			perror("error excve");
	}
}

void	if_arg(t_pipex *pipex)
{
	write(2, "Error: command not found\n", 25);
	close_pipes(pipex);
	close_fds(pipex);
	free(pipex->pipefd);
	free(pipex->pid);
	free_tab(pipex->commands);
	free(pipex->path);
	exit(1);
}

void	if_command_not_found(t_pipex *pipex)
{
	if (pipex->nb_arg == 0)
	{
		write(2, "Error\n", 6);
		free(pipex->commands);
		close_fds(pipex);
	}
	else
		if_arg(pipex);
}
