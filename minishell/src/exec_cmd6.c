/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:00:23 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 11:00:51 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_builtins_status(t_minishell *info)
{
	if (info->command[info->x].exec_array[0])
	{
		if (!ft_strcmp(info->command[info->x].exec_array[0], "cd"))
			info->command[info->x].status_exec = 0;
		else if (!ft_strcmp(info->command[info->x].exec_array[0], "echo"))
			info->command[info->x].status_exec = 0;
		else if (!ft_strcmp(info->command[info->x].exec_array[0], "pwd"))
			info->command[info->x].status_exec = 0;
		else if (!ft_strcmp(info->command[info->x].exec_array[0], "export"))
			info->command[info->x].status_exec = 0;
		else if (!ft_strcmp(info->command[info->x].exec_array[0], "unset"))
			info->command[info->x].status_exec = 0;
		else if (!ft_strcmp(info->command[info->x].exec_array[0], "env"))
			info->command[info->x].status_exec = 0;
		else if (!ft_strcmp(info->command[info->x].exec_array[0], "exit"))
			info->command[info->x].status_exec = 0;
	}
}

void	exec_builtins3(t_minishell *info)
{
	if (!ft_strcmp(info->command[info->x].exec_array[0],
			"exit"))
	{
		info->command[info->x].status_exec = 0;
		if (info->command[info->x].exec_array[1])
		{
			if (info->command[info->x].exec_array[2] == NULL)
			{
				g_exit_status = 0;
				ft_exit(info,
					ft_atoi(info->command[info->x].exec_array[1]),
					info->x);
			}
			else
			{
				g_exit_status = 1;
				printf("Error: exit: too many arguments\n");
			}
		}
		else
			ft_exit(info, 0, info->x);
	}
}

void	exec_builtins2(t_minishell *info)
{
	if (!ft_strcmp(info->command[info->x].exec_array[0],
			"export"))
	{
		info->command[info->x].status_exec = 0;
		ft_export(info, info->command[info->x].exec_array[1],
			info->x);
	}
	else if (!ft_strcmp(info->command[info->x].exec_array[0],
			"unset"))
	{
		info->command[info->x].status_exec = 0;
		ft_unset(info, info->command[info->x].exec_array[1]);
	}
	else if (!ft_strcmp(info->command[info->x].exec_array[0],
			"env"))
	{
		info->command[info->x].status_exec = 0;
		ft_env(info, info->x, 0);
	}
	else
		exec_builtins3(info);
}

void	exec_builtins(t_minishell *info)
{
	if (info->command[info->x].exec_array[0])
	{
		if (!ft_strcmp(info->command[info->x].exec_array[0], "cd"))
		{
			info->command[info->x].status_exec = 0;
			ft_cd(info, info->x);
		}
		else if (!ft_strcmp(info->command[info->x].exec_array[0],
				"echo"))
		{
			info->command[info->x].status_exec = 0;
			ft_echo(info, info->x);
		}
		else if (!ft_strcmp(info->command[info->x].exec_array[0],
				"pwd"))
		{
			info->command[info->x].status_exec = 0;
			ft_pwd(info, info->x, info->command[info->x].exec_array[1]);
		}
		else
			exec_builtins2(info);
	}
}

void	dup2_loop_child(t_minishell *info)
{
	if (dup2(info->command[info->x].pipe_fd[1], 1) == 0)
		exit(g_exit_status);
	if (info->x != 0)
		dup2(info->command[info->x - 1].pipe_fd[0], 0);
	if (info->command[info->x].fd_in != -2)
		dup2(info->command[info->x].fd_in, 0);
	if (info->command[info->x].fd_out != -2)
		dup2(info->command[info->x].fd_out, 1);
}
