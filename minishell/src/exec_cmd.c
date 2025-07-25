/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:20:31 by naben-za          #+#    #+#             */
/*   Updated: 2022/06/02 20:20:48 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_cmd(t_minishell *info)
{
	info->directory = NULL;
	info->pid_status = -1;
	info->x = 0;
	if (pipe(info->command[info->x].pipe_fd) == -1)
	{
		perror("Error");
		return (0);
	}
	info->command[info->x].status_exec = 1;
	check_builtins_status(info);
	while (info->x < info->tokens->nb_pipe)
		if (exec_cmd_loop(info) == 0)
			return (0);
	check_builtins_status(info);
	if (info->command[info->x].status_exec || info->tokens->nb_pipe > 0)
	{
		if (exec_last_cmd(info) == 0)
			return (0);
	}
	else
		builtins_close_pipe_end(info);
	wait_childs(info);
	return (1);
}

int	exec_cmd_loop(t_minishell *info)
{
	info->command[info->x].pid = fork();
	sig_init2();
	if (info->command[info->x].pid == -1)
		return (0);
	if (info->command[info->x].pid == 0)
	{
		dup2_loop_child(info);
		exec_builtins(info);
		close_pipe_loop_child(info);
		if (info->command[info->x].exec_array[0]
			&& access(info->command[info->x].exec_array[0], F_OK) == 0
			&& info->command[info->x].status_exec
			&& (info->command[info->x].exec_array[0][0] == '/'
			|| info->command[info->x].exec_array[0][1] == '/'))
			exec_abs_path_child_loop(info);
		else if (info->command[info->x].status_exec)
			exec_relative_path_child_loop(info);
		exit(g_exit_status);
	}
	else
		if (exec_cmd_parent_loop(info) == 0)
			return (0);
	info->x++;
	return (1);
}

int	exec_last_cmd(t_minishell *info)
{
	info->command[info->x].pid = fork();
	sig_init2();
	if (info->command[info->x].pid == -1)
		return (0);
	if (info->command[info->x].pid == 0)
	{
		dup2_child_last(info);
		exec_builtins(info);
		close_pipes_child_last(info);
		if (info->command[info->x].exec_array[0]
			&& access(info->command[info->x].exec_array[0],
				F_OK | X_OK) == 0
			&& info->command[info->x].status_exec
			&& (info->command[info->x].exec_array[0][0] == '/'
			|| info->command[info->x].exec_array[0][1] == '/'))
			exec_abs_child_last(info);
		else if (info->command[info->x].status_exec)
			exec_relativ_child_last(info);
		exit(g_exit_status);
	}
	else
		close_pipes_parent_last(info);
	return (1);
}

void	wait_childs(t_minishell *info)
{
	info->x = -1;
	while (++info->x <= info->tokens->nb_pipe)
	{
		if (info->command[info->x].exec_array)
			free_tab(info->command[info->x].exec_array);
		if (info->command[info->x].pid > 0)
			waitpid(info->command[info->x].pid, &info->pid_status, 0);
		if (WIFEXITED(info->pid_status))
			g_exit_status = WEXITSTATUS(info->pid_status);
		else if (WIFSIGNALED(info->pid_status))
			g_exit_status = WTERMSIG(info->pid_status);
	}
}

void	close_directory(t_minishell *info)
{
	if (info->directory)
		closedir(info->directory);
}
