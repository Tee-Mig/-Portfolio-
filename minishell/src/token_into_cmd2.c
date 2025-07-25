/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_into_cmd2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:10:02 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 19:47:09 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_heredoc(t_minishell *info)
{
	if (info->command[info->m].fd_in != -2)
		close(info->command[info->m].fd_in);
	if (!access("tmp5684624", F_OK))
		unlink("tmp5684624");
	info->command[info->m].fd_in \
	= ft_heredoc(info->tmp4->next->next->content);
	info->tmp4 = info->tmp4->next;
}

int	do_append(t_minishell *info)
{
	if (info->command[info->m].fd_out != -2)
		close(info->command[info->m].fd_out);
	info->command[info->m].fd_out \
		= open(info->tmp4->next->next->content,
		O_CREAT | O_RDWR | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (info->command[info->m].fd_out == -1)
	{
		info->command[info->m].fd_out = -2;
		return (2);
	}
	info->tmp4 = info->tmp4->next;
	return (1);
}

int	do_replace(t_minishell *info)
{
	if (info->command[info->m].fd_out != -2)
		close(info->command[info->m].fd_out);
	info->command[info->m].fd_out \
	= open(info->tmp4->next->content,
		O_CREAT | O_RDWR | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (info->command[info->m].fd_out == -1)
	{
		info->command[info->m].fd_out = -2;
		return (2);
	}
	return (1);
}

int	do_read(t_minishell *info)
{
	if (info->command[info->m].fd_in != -2)
		close(info->command[info->m].fd_in);
	info->command[info->m].fd_in \
	= open(info->tmp4->next->content, O_RDONLY);
	if (info->command[info->m].fd_in == -1)
	{
		info->command[info->m].fd_in = -2;
		return (2);
	}
	return (1);
}

void	get_nb_of_element(t_minishell *info)
{
	while (info->tmp5 && ft_strcmp((char *)info->tmp5->content, "|"))
	{
		if (info->tmp4->status
			&& ft_strcmp((char *)info->tmp5->status, "chevron"))
			info->nb_exec_array++;
		info->tmp5 = info->tmp5->next;
	}
	info->command[info->m].exec_array \
	= malloc(sizeof(char *) * (info->nb_exec_array + 1));
	info->l = 0;
	while (info->l < info->nb_exec_array + 1)
		info->command[info->m].exec_array[info->l++] = NULL;
	info->l = 0;
}
