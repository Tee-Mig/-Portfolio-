/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:59:12 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 16:00:01 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_error(t_minishell *info)
{
	info->i_main = 0;
	while (info->i_main < info->tokens->nb_pipe + 1)
	{
		if (info->command[info->i_main].exec_array)
			free_tab(info->command[info->i_main].exec_array);
		if (info->command[info->i_main].fd_in != -2
			&& info->command[info->i_main].fd_in != -1)
			close(info->command[info->i_main].fd_in);
		if (info->command[info->i_main].fd_out != -2
			&& info->command[info->i_main].fd_out != -1)
			close(info->command[info->i_main].fd_out);
		info->i_main++;
	}
	if (info->state_token == 0)
		printf("Error: parsing\n");
	g_exit_status = 2;
}

void	input_success(t_minishell *info)
{
	exec_cmd(info);
	info->i_main = 0;
	while (info->i_main < info->tokens->nb_pipe + 1)
	{
		if (info->command[info->i_main].fd_in != -2)
			close(info->command[info->i_main].fd_in);
		if (info->command[info->i_main].fd_out != -2)
			close(info->command[info->i_main].fd_out);
		info->i_main++;
	}
}

int	if_input_valid(t_minishell *info)
{
	get_token(info);
	ft_remove_quote(info, info->tokens);
	info->command \
	= malloc(sizeof(t_command) * (info->tokens->nb_pipe + 1));
	if (!info->command)
	{
		error_malloc_cmd(info);
		return (0);
	}
	info->i_main = -1;
	while (++info->i_main < info->tokens->nb_pipe + 1)
	{
		info->command[info->i_main].fd_in = -2;
		info->command[info->i_main].fd_out = -2;
		info->command[info->i_main].exec_array = NULL;
	}
	info->state_token = token_into_cmd(info);
	if (info->state_token == 1)
		input_success(info);
	else if (info->state_token == 0 || info->state_token == 2)
		input_error(info);
	return (1);
}

int	ft_read_input(t_minishell *info)
{
	sig_init();
	info->tokens->nb_pipe = 0;
	info->input = readline("Minishell$ ");
	if (!info->input)
	{
		printf("exit\n");
		return (0);
	}
	info->command = NULL;
	return (1);
}
