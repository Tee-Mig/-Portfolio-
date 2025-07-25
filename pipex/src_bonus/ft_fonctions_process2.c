/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonctions_process2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:10:24 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 17:05:14 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_middle_pipe(t_pipex *pipex)
{
	close_pipes(pipex);
	close_fds(pipex);
	free(pipex->pipefd);
	free(pipex->pid);
	free_tab(pipex->path);
}

int	init_middle_pipe(t_pipex *pipex)
{
	if (dup2(pipex->pipefd[pipex->index_pipe + 1][1], 1) == -1)
	{
		error_middle_pipe(pipex);
		return (0);
	}
	if (dup2(pipex->pipefd[pipex->index_pipe][0], 0) == -1)
	{
		error_middle_pipe(pipex);
		return (0);
	}
	return (1);
}

void	error_last_pipe(t_pipex *pipex)
{
	close_pipes(pipex);
	close_fds(pipex);
	free(pipex->pipefd);
	free(pipex->pid);
	free_tab(pipex->path);
}

int	if_here_doc(t_pipex *pipex, char **av)
{
	if (pipex->begin_arg == 3)
	{
		if (init_here_doc(pipex) == 0)
			return (0);
		pipex->line = get_next_line(0);
		if (!pipex->line)
		{
			write(2, "Error: get_next_line\n", 21);
			error_here_doc(pipex);
			return (0);
		}
		while (ft_strcmp(av[pipex->begin_arg - 1], pipex->line) != 0)
		{
			write(1, pipex->line, ft_strlen(pipex->line));
			free(pipex->line);
			pipex->line = get_next_line(0);
			if (check_error_line(pipex) == 0)
				return (0);
		}
		free(pipex->line);
		close(pipex->fd_input);
		pipex->fd_input = open_file("tmp", 'i');
	}
	return (1);
}

void	error_first_pipe(t_pipex *pipex)
{
	close_pipes(pipex);
	close_fds(pipex);
	free(pipex->pipefd);
	free(pipex->pid);
	free_tab(pipex->path);
	unlink("tmp");
}
