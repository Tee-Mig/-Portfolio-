/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:51:20 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/17 17:31:21 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_process(char **av, char **envp)
{
	t_pipex	pipex;

	if (get_path(av, envp, &pipex) == 0)
		return ;
	if (get_path2(&pipex, av) == 0)
		return ;
	if (get_path3(&pipex, av) == 0)
		return ;
	if (ft_open_pipe(&pipex, av) == 0)
		return ;
	if (process_child1(&pipex, envp) == 0)
		return ;
	if (process_child2(&pipex, envp, av) == 0)
		return ;
	free_end(&pipex);
}

int	get_path(char **av, char **envp, t_pipex *pipex)
{
	pipex->nb_arg_2 = find_nb_arg(av[2]);
	pipex->nb_arg_3 = find_nb_arg(av[3]);
	pipex->path = NULL;
	pipex->pathcp = NULL;
	pipex->i = -1;
	while (envp[++pipex->i] && strncmp("PATH=", envp[pipex->i], 5) != 0)
		;
	if (!envp[pipex->i])
	{
		ft_putstr("Error: path environment\n");
		return (0);
	}
	pipex->path = ft_split(envp[pipex->i] + 5, ':');
	pipex->pathcp = ft_split(envp[pipex->i] + 5, ':');
	if (get_path_error(pipex) == 0)
		return (0);
	return (1);
}

int	get_path2(t_pipex *pipex, char **av)
{
	pipex->commands1 = ft_split(av[2], ' ');
	pipex->i = -1;
	while (pipex->path[++pipex->i])
	{
		pipex->path[pipex->i] = ft_strjoin(pipex->path[pipex->i], "/");
		pipex->pathcp[pipex->i] = ft_strjoin(pipex->pathcp[pipex->i], "/");
	}
	if (get_path_error2(pipex) == 0)
		return (0);
	return (1);
}

int	get_path3(t_pipex *pipex, char **av)
{
	pipex->commands2 = ft_split(av[3], ' ');
	pipex->i = -1;
	return (1);
}

int	ft_open_pipe(t_pipex *pipex, char **av)
{
	pipex->fd1 = open(av[1], O_RDWR);
	if (pipe(pipex->pipefd) == -1)
	{
		ft_putstr("Error: pipe\n");
		free_tab(pipex->commands1);
		free_tab(pipex->commands2);
		free_tab(pipex->path);
		free_tab(pipex->pathcp);
		close(pipex->fd1);
		return (0);
	}
	return (1);
}
