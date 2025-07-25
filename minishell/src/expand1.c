/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naben-za <naben-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:41:38 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 16:41:54 by naben-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expanding_var(t_minishell *info, t_dlist *tok, int k, int *i)
{
	int	m;

	m = 0;
	info->cp_tmp = ft_strdup("");
	while (m < *i)
	{
		info->cp_tmp = ft_strjoin(info->cp_tmp, tok->unquoted_content[m]);
		m++;
	}
	k++;
	while (info->cp_envp[*tok->norm_helper1][k] != '\0')
	{
		info->cp_tmp = ft_strjoin(info->cp_tmp,
				info->cp_envp[*tok->norm_helper1][k]);
		k++;
		*i += 1;
	}
	*i = *i - 1;
	m += *tok->norm_helper2 + 1;
	while (tok->unquoted_content[m])
	{
		info->cp_tmp = ft_strjoin(info->cp_tmp, tok->unquoted_content[m]);
		m++;
	}
}

void	expand_last_part(t_minishell *info, t_dlist *tok, int *i)
{
	int	m;

	m = 0;
	info->cp_tmp = ft_strdup("");
	while (m < *i)
	{
		info->cp_tmp = ft_strjoin(info->cp_tmp, tok->unquoted_content[m]);
		m++;
	}
	while (tok->unquoted_content[m + *tok->norm_helper2 + 1])
	{
			info->cp_tmp = ft_strjoin(info->cp_tmp,
				tok->unquoted_content[m + *tok->norm_helper2 + 1]);
			m++;
	}
	*i = *i - 1;
	free(tok->unquoted_content);
	tok->unquoted_content = ft_strdup(info->cp_tmp);
	free(info->cp_tmp);
}

void	expand_first_part(t_minishell *info, t_dlist *tok, int i)
{
	int	j;
	int	k;

	j = 0;
	tok->norm_helper1 = &j;
	while (info->cp_envp[j] != NULL)
	{
		k = 0;
		info->var_path = ft_strdup("");
		while ((info->cp_envp[j][k] - '=') != 0)
			info->var_path = ft_strjoin(info->var_path, info->cp_envp[j][k++]);
		if (!ft_strcmp(info->var_expand, info->var_path))
		{
			expanding_var(info, tok, k, &i);
			free(tok->unquoted_content);
			free(info->var_path);
			tok->unquoted_content = ft_strdup(info->cp_tmp);
			free(info->cp_tmp);
			break ;
		}
		free(info->var_path);
		j++;
	}
}

void	ft_expand2(t_minishell *info, t_dlist *tok, int i)
{
	char	*g_status_char;

	while (tok->unquoted_content[i])
	{
		info->cp_tmp = NULL;
		if ((tok->unquoted_content[i] - '$') == 0
			&& (tok->unquoted_content[i + 1] - '?') == 0)
		{
			g_status_char = ft_itoa(g_exit_status);
			expand_exit_status(info, tok, i, g_status_char);
		}
		else if ((tok->unquoted_content[i] - '$') == 0)
		{
			var_to_expand(info, tok, i);
			expand_first_part(info, tok, i);
			if (info->cp_tmp == NULL)
			{
				expand_last_part(info, tok, &i);
			}
			free(info->var_expand);
			i++;
		}
		else
			i++;
	}
}

char	*ft_expand(t_minishell *info, t_dlist *tok, char *quote, int i)
{
	int		len;

	len = 0;
	tok->norm_helper2 = &len;
	if (!info->cp_envp)
		return (NULL);
	if (!ft_strcmp(quote, "double") || !ft_strcmp(quote, "none"))
		ft_expand2(info, tok, i);
	return (tok->unquoted_content);
}
