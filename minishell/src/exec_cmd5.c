/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:57:47 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 20:20:40 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_abs_child_last2(t_minishell *info)
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
}

void	exec_abs_child_last(t_minishell *info)
{
	g_exit_status = 0;
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
			close_directory(info);
			printf("%s: Is a directory\n",
				info->command[info->x].exec_array[0]);
			g_exit_status = 126;
		}
		else
		{
			close_directory(info);
			perror("Error");
		}
	}
	exec_abs_child_last2(info);
	exit(g_exit_status);
}

void	exec_relative_find_last2(t_minishell *info)
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

void	exec_relative_find_last(t_minishell *info)
{
	info->tmp_free = info->command[info->x].exec_array[0];
	info->command[info->x].exec_array[0] = info->path_exec2;
	g_exit_status = 0;
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
	exec_relative_find_last2(info);
}

void	close_pipes_relative_child_last(t_minishell *info)
{
	info->z = 0;
	while (info->z < info->tokens->nb_pipe + 1)
	{
		if (info->command[info->z].fd_in != -2)
			close(info->command[info->z].fd_in);
		if (info->command[info->z].fd_out != -2)
			close(info->command[info->z].fd_out);
		info->z++;
	}
	dup2(2, 1);
}
