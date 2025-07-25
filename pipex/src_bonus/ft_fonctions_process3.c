/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonctions_process3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:12:05 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 16:54:35 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	init_pid_and_pipe(t_pipex *pipex, int ac)
{
	pipex->nb_command = ac - pipex->begin_arg - 1;
	pipex->pid = malloc(sizeof(pid_t) * (pipex->nb_command));
	if (!pipex->pid)
	{
		ft_putstr("Error: malloc\n");
		close_fds(pipex);
		free_tab(pipex->path);
		return (0);
	}
	pipex->pipefd = malloc(sizeof(int *) * pipex->nb_command - 1);
	if (!pipex->pipefd)
	{
		ft_putstr("Error: malloc\n");
		close_fds(pipex);
		free(pipex->pid);
		free_tab(pipex->path);
		return (0);
	}
	if (malloc_pipe(pipex) == 0)
		return (0);
	return (1);
}

void	error_here_doc(t_pipex *pipex)
{
	close_pipes(pipex);
	close_fds(pipex);
	free(pipex->pipefd);
	free(pipex->pid);
	free_tab(pipex->path);
}

int	init_here_doc(t_pipex *pipex)
{
	pipex->fd_input = open_file("tmp", 'h');
	if (pipex->fd_input == -1)
	{
		ft_putstr("Error: open\n");
		error_here_doc(pipex);
		return (0);
	}
	if (dup2(pipex->fd_input, 1) == -1)
	{
		ft_putstr("Error: dup2\n");
		error_here_doc(pipex);
		return (0);
	}
	return (1);
}

int	check_error_line(t_pipex *pipex)
{
	if (!pipex->line)
	{
		write(2, "Error: get_next_line\n", 21);
		error_here_doc(pipex);
		return (0);
	}
	return (1);
}
