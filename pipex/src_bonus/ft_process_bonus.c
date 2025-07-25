/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:51:20 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 16:46:13 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_process_bonus(char **av, char **envp, t_pipex *pipex, int ac)
{
	if (get_path_env(pipex, envp) == 0)
		return ;
	if (init_pid_and_pipe(pipex, ac) == 0)
		return ;
	if (if_here_doc(pipex, av) == 0)
		return ;
	if (first_pipe(pipex, av, envp) == 0)
		return ;
	if (middle_pipe(pipex, av, envp, ac) == 0)
		return ;
	if (last_pipe(pipex, av, envp) == 0)
		return ;
	close_pipes(pipex);
	pipex->index_pid = -1;
	while (++pipex->index_pid < pipex->nb_command)
		waitpid(pipex->pid[pipex->index_pid], NULL, 0);
	free(pipex->pipefd);
	free(pipex->pid);
	free_tab(pipex->path);
	close_fds(pipex);
}

int	first_pipe(t_pipex *pipex, char **av, char **envp)
{
	pipex->index_pid = 0;
	pipex->pid[pipex->index_pid] = fork();
	if (pipex->pid[pipex->index_pid] == 0)
	{
		if (dup2(pipex->pipefd[0][1], 1) == -1)
		{
			error_first_pipe(pipex);
			return (0);
		}
		if (dup2(pipex->fd_input, 0) == -1)
		{
			error_first_pipe(pipex);
			return (0);
		}
		pipex->i = -1;
		while (++pipex->i < pipex->nb_command - 1)
		{
			close(pipex->pipefd[pipex->i][0]);
			close(pipex->pipefd[pipex->i][1]);
		}
		exec_command(pipex, av, envp);
	}
	if (pipex->begin_arg == 3)
		unlink("tmp");
	return (1);
}

int	middle_pipe(t_pipex *pipex, char **av, char **envp, int ac)
{
	pipex->index_pid++;
	pipex->index_pipe = 0;
	while (++pipex->begin_arg < ac - 2)
	{
		pipex->pid[pipex->index_pid] = fork();
		if (pipex->pid[pipex->index_pid] == 0)
		{
			if (init_middle_pipe(pipex) == 0)
				return (0);
			pipex->i = -1;
			while (++pipex->i < pipex->nb_command - 1)
			{
				close(pipex->pipefd[pipex->i][0]);
				close(pipex->pipefd[pipex->i][1]);
			}
			exec_command(pipex, av, envp);
		}
		pipex->index_pipe++;
		pipex->index_pid++;
	}
	return (1);
}

int	last_pipe(t_pipex *pipex, char **av, char **envp)
{
	pipex->pid[pipex->index_pid] = fork();
	if (pipex->pid[pipex->index_pid] == 0)
	{
		if (dup2(pipex->fd_output, 1) == -1)
		{
			error_last_pipe(pipex);
			return (0);
		}
		if (dup2(pipex->pipefd[pipex->nb_command - 2][0], 0) == -1)
		{
			error_last_pipe(pipex);
			return (0);
		}
		pipex->i = -1;
		while (++pipex->i < pipex->nb_command - 1)
		{
			close(pipex->pipefd[pipex->i][0]);
			close(pipex->pipefd[pipex->i][1]);
		}
		exec_command(pipex, av, envp);
	}
	return (1);
}
