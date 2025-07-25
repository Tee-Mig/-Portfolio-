/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naben-za <naben-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:48:29 by naben-za          #+#    #+#             */
/*   Updated: 2022/06/02 18:24:28 by naben-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	utils_free(t_minishell *info, t_dlist *tok, char *g_status_char)
{
	free(g_status_char);
	free(tok->unquoted_content);
	tok->unquoted_content = ft_strdup(info->cp_tmp);
	free(info->cp_tmp);
}

void	expand_exit_status(t_minishell *info, t_dlist *tok, int i,
			char *g_status_char)
{
	int	m;
	int	j;

	m = 0;
	j = 0;
	info->cp_tmp = ft_strdup("");
	while (m < i)
	{
		info->cp_tmp = ft_strjoin(info->cp_tmp, tok->unquoted_content[m]);
		m++;
	}
	while (g_status_char[j] != '\0')
	{
		info->cp_tmp = ft_strjoin(info->cp_tmp, g_status_char[j]);
		j++;
	}
	m += 2;
	while (tok->unquoted_content[m])
	{
		info->cp_tmp = ft_strjoin(info->cp_tmp, tok->unquoted_content[m]);
		m++;
	}
	utils_free(info, tok, g_status_char);
}

void	var_to_expand(t_minishell *info, t_dlist *tok, int i)
{
	int	k;
	int	j;

	j = 0;
	k = i + 1;
	while (tok->unquoted_content[k + *tok->norm_helper2] != '$'
		&& tok->unquoted_content[k + *tok->norm_helper2] != ' '
		&& tok->unquoted_content[k + *tok->norm_helper2] != '\0'
		&& tok->unquoted_content[k + *tok->norm_helper2] != '\'')
	{
		*tok->norm_helper2 += 1;
	}
	info->var_expand = ft_strdup("");
	j = 0;
	while (j < *tok->norm_helper2)
	{
		info->var_expand = ft_strjoin(info->var_expand,
				tok->unquoted_content[k + j]);
		j++;
	}
}
