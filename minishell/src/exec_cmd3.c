/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:58:24 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/03 11:41:14 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_relative_path_child_loop2(t_minishell *info)
{
	dup2(2, 1);
	if (info->command[info->x].exec_array[0])
		info->directory = opendir(info->command[info->x].exec_array[0]);
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

void	exec_relative_path_child_loop(t_minishell *info)
{
	info->y = -1;
	while (info->command[info->x].exec_array[0]
		&& info->path && info->path[++info->y])
	{
		info->path_exec2 = ft_strjoin_str(info->path[info->y],
				info->command[info->x].exec_array[0]);
		if (info->command[info->x].exec_array[0][0] != '\0'
			&& access(info->path_exec2, F_OK | X_OK) == 0)
			exec_relative_path_find_loop_child(info);
		free(info->path_exec2);
	}
	info->z = 0;
	while (info->z < info->tokens->nb_pipe + 1)
	{
		if (info->command[info->z].fd_in != -2)
			close(info->command[info->z].fd_in);
		if (info->command[info->z].fd_out != -2)
			close(info->command[info->z].fd_out);
		info->z++;
	}
	exec_relative_path_child_loop2(info);
}

int	exec_cmd_parent_loop(t_minishell *info)
{
	info->command[info->x + 1].status_exec = 1;
	if (info->x < info->tokens->nb_pipe)
	{
		if (pipe(info->command[info->x + 1].pipe_fd) == -1)
			return (0);
	}
	if (info->x != 0)
	{
		close(info->command[info->x - 1].pipe_fd[0]);
		close(info->command[info->x].pipe_fd[1]);
	}
	else
		close(info->command[info->x].pipe_fd[1]);
	return (1);
}

void	dup2_child_last(t_minishell *info)
{
	if (info->x != 0)
		dup2(info->command[info->x - 1].pipe_fd[0], 0);
	if (info->command[info->x].fd_in != -2)
		dup2(info->command[info->x].fd_in, 0);
	if (info->command[info->x].fd_out != -2)
		dup2(info->command[info->x].fd_out, 1);
}

void	close_pipes_child_last(t_minishell *info)
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
