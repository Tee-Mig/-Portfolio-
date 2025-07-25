/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:31:56 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/01 16:37:44 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_token(t_minishell *info)
{
	info->tokens->nb_pipe = 0;
	get_token_part1(info);
	get_token_part2(info);
}

void	get_token_part1(t_minishell *info)
{
	info->i = -1;
	while (info->input[++info->i])
	{
		while (info->input[info->i] == ' '
			|| info->input[info->i] == '\t' || info->input[info->i] == '\n')
				info->i++;
		info->token = ft_strdup("");
		while (info->input[info->i] != ' ' && info->input[info->i] != '\t'
			&& info->input[info->i] != '\n' && info->input[info->i] != 0)
			get_token_quote(info);
		if (info->token[0] != '\'' && info->token[0] != '\"')
		{
			get_token_sep(info);
		}
		else
			add_last(info->tokens, (char *)info->token);
		if (info->input[info->i] == 0)
			break ;
	}
}

void	get_token_quote(t_minishell *info)
{
	if (info->input[info->i] == '\'')
	{
		info->token = ft_strjoin(info->token, info->input[info->i]);
		info->i++;
		while (info->input[info->i] != '\'')
			info->token = ft_strjoin(info->token,
					info->input[info->i++]);
		info->token = ft_strjoin(info->token, info->input[info->i]);
		info->i++;
	}
	else if (info->input[info->i] == '\"')
	{
		info->token = ft_strjoin(info->token, info->input[info->i]);
		info->i++;
		while (info->input[info->i] != '\"')
			info->token = ft_strjoin(info->token,
					info->input[info->i++]);
		info->token = ft_strjoin(info->token, info->input[info->i]);
		info->i++;
	}
	else
		info->token = ft_strjoin(info->token, info->input[info->i++]);
}

void	get_no_sep(t_minishell *info)
{
	info->token2 = ft_strdup("");
	while (!is_delimiter(info->token[info->j])
		&& info->token[info->j])
	{
		info->token2 = ft_strjoin(info->token2,
				info->token[info->j]);
		info->j++;
	}
	if (info->token2[0] != '\0')
		add_last(info->tokens, (char *)info->token2);
}

void	get_token_sep(t_minishell *info)
{
	info->j = 0;
	while (info->token[info->j])
	{
		if (is_delimiter(info->token[info->j]) && info->token[info->j])
		{
			while (is_delimiter(info->token[info->j])
				&& info->token[info->j])
			{
				info->char_tmp = malloc(sizeof(char) * 2);
				info->char_tmp[0] = info->token[info->j];
				info->char_tmp[1] = '\0';
				add_last(info->tokens, info->char_tmp);
				info->j++;
			}
		}
		else if (!is_delimiter(info->token[info->j])
			&& info->token[info->j])
			get_no_sep(info);
	}
	free(info->token);
}
