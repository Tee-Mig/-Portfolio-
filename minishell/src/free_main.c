/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:54:41 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 15:57:15 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_end(t_minishell *info)
{
	if (info->path)
		free_tab(info->path);
	if (info->cp_envp)
		free_tab(info->cp_envp);
	free(info->tokens);
	free(info->garbage_collector);
}

void	error_malloc_cmd(t_minishell *info)
{
	info->i_main = -1;
	info->tmp2_main = info->garbage_collector->head;
	while (++info->i_main < info->garbage_collector->size)
	{
		free(info->tmp2_main->content);
		info->tmp2_main = info->tmp2_main->next;
	}
	info->i_main = -1;
	info->tmp_main = info->tokens->head;
	while (++info->i_main < info->tokens->size)
	{
		free(info->tmp_main->content);
		info->tmp_main = info->tmp_main->next;
	}
	if (info->tokens->size != 0)
		free_list(info->tokens);
	if (info->garbage_collector->size != 0)
		free_list(info->garbage_collector);
	printf("Error: malloc\n");
	free(info->input);
}

int	free_tokens2(t_minishell *info)
{
	info->i_main = -1;
	info->tmp2_main = info->garbage_collector->head;
	while (++info->i_main < info->garbage_collector->size)
	{
		free(info->tmp2_main->content);
		info->tmp2_main = info->tmp2_main->next;
	}
	add_history(info->input);
	if (info->tokens->size != 0)
		free_list(info->tokens);
	if (info->garbage_collector->size != 0)
		free_list(info->garbage_collector);
	if (update_path(info) == 0)
		return (0);
	if (info->command != NULL && ft_strcmp(info->input, ""))
		free(info->command);
	if (info->input)
		free(info->input);
	return (1);
}

int	free_tokens(t_minishell *info)
{
	info->i_main = -1;
	info->tmp_main = info->tokens->head;
	while (++info->i_main < info->tokens->size)
	{
		if (!ft_strcmp(info->tmp_main->status, "error_path"))
			free(info->tmp_main->status);
		free(info->tmp_main->content);
		info->tmp_main = info->tmp_main->next;
	}
	if (!access("tmp5684624", F_OK))
		unlink("tmp5684624");
	if (free_tokens2(info) == 0)
		return (0);
	return (1);
}
