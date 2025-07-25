/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 20:25:47 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 16:44:53 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac >= 6)
	{
		if (init_file_here_doc(&pipex, av, ac) == 0)
			return (1);
	}
	else if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6)
	{
		ft_putstr("Error: arguments\n");
		return (1);
	}
	else if (ac >= 5)
	{
		if (init_no_here_doc(&pipex, av, ac) == 0)
			return (1);
	}
	else
	{
		ft_putstr("Error: arguments\n");
		return (1);
	}
	ft_process_bonus(av, envp, &pipex, ac);
	return (0);
}

int	init_file_here_doc(t_pipex *pipex, char **av, int ac)
{
	pipex->begin_arg = 3;
	pipex->fd_input = -1;
	pipex->fd_output = open_file(av[ac - 1], 'h');
	if (pipex->fd_output == -1)
	{
		ft_putstr("Error: file\n");
		return (0);
	}
	return (1);
}

int	init_no_here_doc(t_pipex *pipex, char **av, int ac)
{
	pipex->begin_arg = 2;
		pipex->fd_input = open_file(av[1], 'i');
	if (pipex->fd_input == -1)
	{
		ft_putstr("Error: file\n");
		return (0);
	}
	pipex->fd_output = open_file(av[ac - 1], 'o');
	if (pipex->fd_output == -1)
	{
		ft_putstr("Error: file\n");
		close(pipex->fd_input);
		return (0);
	}
	return (1);
}
