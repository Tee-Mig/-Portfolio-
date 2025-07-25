/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:59:15 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 20:16:52 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe_loop_child(t_minishell *info)
{
	if (info->x != 0)
	{
		close(info->command[info->x - 1].pipe_fd[0]);
		close(info->command[info->x].pipe_fd[0]);
		close(info->command[info->x].pipe_fd[1]);
	}
	else
	{
		close(info->command[info->x].pipe_fd[1]);
		close(info->command[info->x].pipe_fd[0]);
	}
}

void	exec_abs_path_child_loop2(t_minishell *info)
{
	info->z = 0;
	free_tab(info->command[info->x].exec_array);
	while (info->z < info->tokens->nb_pipe + 1)
	{
		if (info->command[info->z].fd_in != -2)
			close(info->command[info->z].fd_in);
		if (info->command[info->z].fd_out != -2)
			close(info->command[info->z].fd_out);
		info->z++;
	}
	exit(g_exit_status);
}

void	exec_abs_path_child_loop(t_minishell *info)
{
	if (execve(info->command[info->x].exec_array[0],
			info->command[info->x].exec_array, info->cp_envp) == -1)
	{
		g_exit_status = 126;
		if (info->command[info->x].exec_array[0])
			info->directory \
			= opendir(info->command[info->x].exec_array[0]);
		dup2(2, 1);
		if (info->directory != NULL)
		{
			if (info->directory)
				closedir(info->directory);
			printf("%s: Is a directory\n",
				info->command[info->x].exec_array[0]);
			g_exit_status = 126;
		}
		else
		{
			if (info->directory)
				closedir(info->directory);
			perror("Error");
		}
	}
	exec_abs_path_child_loop2(info);
}

void	exec_relative_path_find_loop_child2(t_minishell *info)
{
	if (info->tmp_free[0] == '.'
		&& info->tmp_free[1] && info->tmp_free[1] == '.')
	{
		g_exit_status = 127;
		printf("%s: command not found\n", info->tmp_free);
	}
	else if (info->tmp_free[0] == '.')
	{
		g_exit_status = 2;
		printf("%s: filename argument required\n",
			info->tmp_free);
	}
	free(info->tmp_free);
	exit(g_exit_status);
}

void	exec_relative_path_find_loop_child(t_minishell *info)
{
	info->tmp_free = info->command[info->x].exec_array[0];
	info->command[info->x].exec_array[0] = info->path_exec2;
	if (info->tmp_free[0] != '.'
		&& execve(info->path_exec2,
			info->command[info->x].exec_array,
			info->cp_envp) == -1)
		perror("Error");
	g_exit_status = 126;
	dup2(2, 1);
	info->z = 0;
	free_tab(info->command[info->x].exec_array);
	while (info->z < info->tokens->nb_pipe + 1)
	{
		if (info->command[info->z].fd_in != -2)
			close(info->command[info->z].fd_in);
		if (info->command[info->z].fd_out != -2)
			close(info->command[info->z].fd_out);
		info->z++;
	}
	exec_relative_path_find_loop_child2(info);
}
