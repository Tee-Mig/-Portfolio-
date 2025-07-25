/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:57:28 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/03 11:41:21 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_relativ_child_last2(t_minishell *info)
{
	if (info->command[info->x].exec_array[0] != 0
		&& ft_strchr(info->command[info->x].exec_array[0], '/') \
		== NULL)
	{
		g_exit_status = 127;
		printf("%s: command not found\n",
			info->command[info->x].exec_array[0]);
		free_tab(info->command[info->x].exec_array);
	}
	else if (info->command[info->x].exec_array[0] != 0
		&& (info->path == NULL || info->directory == NULL))
	{
		g_exit_status = 127;
		printf("%s: No such file or directory\n",
			info->command[info->x].exec_array[0]);
		free_tab(info->command[info->x].exec_array);
	}
	else
		printf("No such file or directory\n");
	if (info->directory)
		closedir(info->directory);
	exit(g_exit_status);
}

void	exec_relativ_child_last(t_minishell *info)
{
	info->y = -1;
	while (info->command[info->x].exec_array[0]
		&& info->path && info->path[++info->y])
	{
		info->path_exec2 = ft_strjoin_str(info->path[info->y],
				info->command[info->x].exec_array[0]);
		if (info->command[info->x].exec_array[0][0] != '\0'
				&& access(info->path_exec2, F_OK | X_OK) == 0)
			exec_relative_find_last(info);
		free(info->path_exec2);
	}
	close_pipes_relative_child_last(info);
	if (info->command[info->x].exec_array[0])
		info->directory = opendir(info->command[info->x].exec_array[0]);
	exec_relativ_child_last2(info);
}

void	close_pipes_parent_last(t_minishell *info)
{
	if (info->x == 0)
	{
		close(info->command[info->x].pipe_fd[0]);
		close(info->command[info->x].pipe_fd[1]);
	}
	else
	{
		close(info->command[info->x].pipe_fd[0]);
		close(info->command[info->x].pipe_fd[1]);
		close(info->command[info->x - 1].pipe_fd[0]);
	}
}

void	builtins_close_pipe_end(t_minishell *info)
{
	exec_builtins(info);
	if (info->x == 0)
	{
		close(info->command[info->x].pipe_fd[0]);
		close(info->command[info->x].pipe_fd[1]);
	}
	else
	{
		close(info->command[info->x].pipe_fd[0]);
		close(info->command[info->x].pipe_fd[1]);
		close(info->command[info->x - 1].pipe_fd[0]);
	}
}
