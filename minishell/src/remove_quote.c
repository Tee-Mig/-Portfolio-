/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naben-za <naben-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:19:24 by naben-za          #+#    #+#             */
/*   Updated: 2022/06/02 15:11:46 by naben-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	d_quote(t_minishell *info, t_node *tmp, t_dlist *tok, size_t *i)
{
	size_t	j;

	tok->id_first_quote = *i;
	tok->id_last_quote = tok->id_first_quote + 1;
	while (tok->tmp_content[tok->id_last_quote] != '\"')
		tok->id_last_quote++;
	tok->id_first_quote++;
	j = 0;
	while (tok->unquoted_content[j] != '\0')
		++j;
	while (tok->id_first_quote < tok->id_last_quote)
			tok->unquoted_content = ft_strjoin(tok->unquoted_content,
				tok->tmp_content[tok->id_first_quote++]);
	tok->unquoted_content = ft_expand(info, tok, "double", j);
	tok->id_last_quote++;
	*i = tok->id_last_quote;
	if (tok->tmp_content[*i] == '\0')
	{
		free(tok->tmp_content);
		tmp->content = tok->unquoted_content;
		return (0);
	}
	return (1);
}

int	s_quote(t_node *tmp, t_dlist *tok, size_t *i)
{
	tok->id_first_quote = *i;
	tok->id_last_quote = tok->id_first_quote + 1;
	while (tok->tmp_content[tok->id_last_quote] != '\'')
		tok->id_last_quote++;
	tok->id_first_quote++;
	while (tok->id_first_quote < tok->id_last_quote)
			tok->unquoted_content = ft_strjoin(tok->unquoted_content,
				tok->tmp_content[tok->id_first_quote++]);
	tok->id_last_quote++;
	*i = tok->id_last_quote;
	if (tok->tmp_content[*i] == '\0')
	{
		free(tok->tmp_content);
		tmp->content = tok->unquoted_content;
		return (0);
	}
	return (1);
}

int	no_quote(t_minishell *info, t_node *tmp, t_dlist *tok, size_t *i)
{
	size_t	j;

	tok->id_first_quote = *i;
	tok->id_last_quote = tok->id_first_quote + 1;
	while (tok->tmp_content[tok->id_last_quote] != '\"'
		&& tok->tmp_content[tok->id_last_quote] != '\''
		&& tok->tmp_content[tok->id_last_quote] != '\0')
		tok->id_last_quote++;
	j = 0;
	while (tok->unquoted_content[j])
		++j;
	while (tok->id_first_quote < tok->id_last_quote)
			tok->unquoted_content = ft_strjoin(tok->unquoted_content,
				tok->tmp_content[tok->id_first_quote++]);
	tok->unquoted_content = ft_expand(info, tok, "none", j);
	*i = tok->id_last_quote;
	if (tok->tmp_content[*i] == '\0')
	{
		free(tok->tmp_content);
		tmp->content = tok->unquoted_content;
		return (0);
	}
	return (1);
}

void	ft_select_quote(t_minishell *info, t_node *tmp, t_dlist *tok)
{
	size_t	i;

	i = 0;
	while (tok->tmp_content[i])
	{
		if (tok->tmp_content[i] == '\"')
		{
			if (d_quote(info, tmp, tok, &i) == 0)
				break ;
		}
		else if (tok->tmp_content[i] == '\'')
		{
			if (s_quote(tmp, tok, &i) == 0)
				break ;
		}
		else
		{
			if (no_quote(info, tmp, tok, &i) == 0)
				break ;
		}
	}
}

int	ft_remove_quote(t_minishell *info, t_dlist *tokens)
{
	t_dlist	*tok;
	t_node	*tmp;

	tok = tokens;
	tmp = tokens->head;
	tok->unquoted_content = NULL;
	while (tmp != NULL)
	{
		tok->id_first_quote = 0;
		tok->tmp_content = (char *)tmp->content;
		tok->unquoted_content = ft_strdup("");
		ft_select_quote(info, tmp, tok);
		tmp = tmp->next;
	}
	return (1);
}
