/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:08:44 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/17 15:52:15 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_end(t_pipex *pipex)
{
	free_tab(pipex->commands1);
	free_tab(pipex->commands2);
	free_tab(pipex->path);
	free_tab(pipex->pathcp);
	close(pipex->pipefd[1]);
	close(pipex->pipefd[0]);
	if (pipex->fd1 != -1)
		close(pipex->fd1);
	close(pipex->fd2);
	waitpid(pipex->id1, NULL, 0);
	waitpid(pipex->id2, NULL, 0);
}

int	get_path_error2(t_pipex *pipex)
{
	if (pipex->path[0] == NULL)
	{
		ft_putstr("Error: malloc\n");
		if (pipex->pathcp[0] != NULL)
			free(pipex->pathcp);
		if (pipex->pathcp != NULL)
			free(pipex->pathcp);
		free(pipex->path);
		free_tab(pipex->commands1);
		return (0);
	}
	if (pipex->pathcp[0] == NULL)
	{
		ft_putstr("Error: malloc\n");
		if (pipex->path[0] != NULL)
			free(pipex->path);
		if (pipex->path != NULL)
			free(pipex->path);
		free(pipex->pathcp);
		free_tab(pipex->commands1);
		return (0);
	}
	return (1);
}

int	get_path_error(t_pipex *pipex)
{
	if (pipex->path == NULL)
	{
		ft_putstr("Error: malloc\n");
		if (pipex->pathcp != NULL)
			free_tab(pipex->pathcp);
		return (0);
	}
	if (pipex->pathcp == NULL)
	{
		ft_putstr("Error: malloc\n");
		if (pipex->path != NULL)
			free_tab(pipex->path);
		return (0);
	}
	return (1);
}
