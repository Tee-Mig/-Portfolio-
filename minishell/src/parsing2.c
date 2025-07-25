/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:29:28 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/01 16:33:13 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_end_path(t_minishell *info, int *i)
{
	*i = -1;
	while (info->path[++*i])
		info->path[*i] = ft_strjoin(info->path[*i], '/');
	if (!info->path[0])
	{
		printf("Error: malloc\n");
		return (0);
	}
	return (1);
}

int	check_quote(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
		{
			while (input[++i] != '\'')
			{
				if (input[i] == '\0')
					return (0);
			}
		}
		else if (input[i] == '\"')
		{
			while (input[++i] != '\"')
			{
				if (input[i] == '\0')
					return (0);
			}
		}
	}
	return (1);
}

void	get_token_part2(t_minishell *info)
{
	info->tmp2 = info->tokens->head;
	while (info->tmp2 != NULL)
	{
		if (!ft_strcmp(info->tmp2->content, "<")
			|| !ft_strcmp(info->tmp2->content, "<<")
			|| !ft_strcmp(info->tmp2->content, ">>")
			|| !ft_strcmp(info->tmp2->content, ">"))
		{
			info->tmp2->status = ft_strdup("chevron");
			add_last(info->garbage_collector, info->tmp2->status);
		}
		else if (!ft_strcmp(info->tmp2->content, "|"))
		{
			info->tmp2->status = ft_strdup("pipe");
			add_last(info->garbage_collector, info->tmp2->status);
			info->tokens->nb_pipe++;
		}
		else
			get_if_no_sep(info);
		info->tmp2 = info->tmp2->next;
	}
}

void	get_if_no_sep(t_minishell *info)
{
	info->j = 0;
	if (info->path)
	{
		while (info->path[info->j])
		{
			info->path_exec = ft_strjoin_str(info->path[info->j],
					info->tmp2->content);
			if (if_cmd_or_error(info) == 0)
				break ;
			info->j++;
			free(info->path_exec);
		}
		if (!access(info->tmp2->content, F_OK))
		{
			info->tmp2->status = ft_strdup("file");
			add_last(info->garbage_collector, info->tmp2->status);
		}
	}
	else
		info->tmp2->status = ft_strdup("error_path");
}

int	if_cmd_or_error(t_minishell *info)
{
	if (!access(info->path_exec, X_OK))
	{
		free(info->path_exec);
		info->tmp2->status = ft_strdup("command");
		add_last(info->garbage_collector, info->tmp2->status);
		return (0);
	}
	else
	{
		info->tmp2->status = ft_strdup("error");
		add_last(info->garbage_collector, info->tmp2->status);
	}
	return (1);
}
