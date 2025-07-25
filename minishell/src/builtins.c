/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naben-za <naben-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:00:46 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 18:30:06 by naben-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd2(t_minishell *info, int i, char *option)
{
	int	j;

	if (option && option[0] == '-')
	{
		j = 1;
		while (option[j])
		{
			if (option[j] != 'L' && option[j] != 'P')
			{
				if (info->command[i].fd_out != -2)
				{
					write(info->command[i].fd_out, "pwd: usage: pwd [-LP]",
						ft_strlen("pwd: usage: pwd [-LP]"));
					write(info->command[i].fd_out, "\n", 1);
				}
				else
					printf("pwd: usage: pwd [-LP]\n");
				g_exit_status = 2;
				return (1);
			}
			j++;
		}
	}
	return (0);
}

void	ft_pwd(t_minishell *info, int i, char *option)
{
	char	path[10000];

	if (ft_pwd2(info, i, option) == 0)
	{
		if (!getcwd(path, 10000))
		{
			perror("Error");
			g_exit_status = 1;
		}
		else
		{
			if (info->command[i].fd_out != -2)
			{
				write(info->command[i].fd_out, path, ft_strlen(path));
				write(info->command[i].fd_out, "\n", 1);
			}
			else
				printf("%s\n", path);
			g_exit_status = 0;
		}
	}
}

void	ft_print_env(t_minishell *info, int id, int status)
{
	int	i;

	i = 0;
	while (info->cp_envp[i] != NULL)
	{
		if (info->command[id].fd_out != -2)
		{
			if (status == 1)
				write(info->command[id].fd_out, "Export ", 7);
			write(info->command[id].fd_out,
				info->cp_envp[i], ft_strlen(info->cp_envp[i]));
			write(info->command[id].fd_out, "\n", 1);
		}
		else
		{
			if (status == 1)
				printf("Export ");
			printf("%s\n", info->cp_envp[i]);
		}
		i++;
	}
}

int	ft_env(t_minishell *info, int id, int status)
{
	if (info->cp_envp[0])
	{
		ft_print_env(info, id, status);
		return (1);
	}
	g_exit_status = 0;
	return (0);
}

int	ft_exit(t_minishell *info, int status, int i)
{
	(void)info;
	if (i == 0)
	{
		close(info->command[i].pipe_fd[0]);
		close(info->command[i].pipe_fd[1]);
	}
	else
	{
		close(info->command[i].pipe_fd[0]);
		close(info->command[i].pipe_fd[1]);
		close(info->command[i - 1].pipe_fd[0]);
	}
	if (info->tokens->nb_pipe == 0)
		printf("exit\n");
	g_exit_status = status;
	exit(status);
	return (1);
}
