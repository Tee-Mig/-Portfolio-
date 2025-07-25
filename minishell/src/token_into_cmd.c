/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_into_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:45:43 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 19:48:51 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_into_cmd(t_minishell *info)
{
	info->m = 0;
	while (info->m < info->tokens->nb_pipe + 1)
	{
		info->command[info->m].pid = -2;
		info->m++;
	}
	info->m = 0;
	info->tmp4 = info->tokens->head;
	info->tmp6 = info->tokens->head;
	if (!ft_strcmp((char *)info->tmp6->content, "|"))
		return (0);
	while (info->tmp6->next != NULL)
		info->tmp6 = info->tmp6->next;
	if (!ft_strcmp((char *)info->tmp6->content, "|"))
		return (0);
	while (info->tmp4 != NULL)
	{
		info->return_val = get_exec_array(info);
		if (info->return_val != 1)
			return (info->return_val);
	}
	return (1);
}

int	check_redir2(t_minishell *info)
{
	if (!ft_strcmp((char *)info->tmp4->content, ">")
		&& info->tmp4->next
		&& !is_delimiter_str((char *)info->tmp4->next->content))
	{
		if (do_replace(info) == 2)
			return (2);
	}
	else if (!ft_strcmp((char *)info->tmp4->content, "<")
		&& info->tmp4->next
		&& !is_delimiter_str((char *)info->tmp4->next->content))
	{
		if (do_read(info) == 2)
			return (2);
	}
	else
	{
		info->command[info->m].exec_array[info->l] = NULL;
		return (0);
	}
	return (1);
}

int	check_redir(t_minishell *info)
{
	if (!ft_strcmp((char *)info->tmp4->content, "<")
		&& info->tmp4->next
		&& !ft_strcmp((char *)info->tmp4->next->content, "<")
		&& info->tmp4->next->next
		&& !is_delimiter_str((char *) \
		info->tmp4->next->next->content))
		do_heredoc(info);
	else if (!ft_strcmp((char *)info->tmp4->content, ">")
		&& info->tmp4->next
		&& !ft_strcmp((char *)info->tmp4->next->content, ">")
		&& info->tmp4->next->next
		&& !is_delimiter_str((char *) \
		info->tmp4->next->next->content))
	{
		if (do_append(info) == 2)
			return (2);
	}
	else
	{
		info->return_val4 = check_redir2(info);
		if (info->return_val4 != 1)
			return (info->return_val4);
	}
	info->tmp4 = info->tmp4->next;
	return (1);
}

int	fill_array(t_minishell *info)
{
	if (info->tmp4->status
		&& ft_strcmp((char *)info->tmp4->status, "chevron"))
	{
		info->command[info->m].exec_array[info->l] \
		= ft_strdup(info->tmp4->content);
		info->l++;
	}
	else
	{
		info->return_val2 = check_redir(info);
		if (info->return_val2 != 1)
			return (info->return_val2);
	}
	if (info->tmp4)
		info->tmp4 = info->tmp4->next;
	return (1);
}

int	get_exec_array(t_minishell *info)
{
	info->nb_exec_array = 0;
	info->tmp5 = info->tmp4;
	if (ft_strcmp((char *)info->tmp5->content, "|"))
	{
		get_nb_of_element(info);
		while (info->tmp4 && ft_strcmp((char *)info->tmp4->content, "|"))
		{
			info->return_val3 = fill_array(info);
			if (info->return_val3 != 1)
			{
				while (info->tmp4
					&& ft_strcmp((char *)info->tmp4->content, "|"))
					info->tmp4 = info->tmp4->next;
			}
		}
		info->command[info->m].exec_array[info->l] = NULL;
		info->m++;
	}
	else
		info->tmp4 = info->tmp4->next;
	return (1);
}
