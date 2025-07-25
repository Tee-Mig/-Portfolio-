/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naben-za <naben-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:11:47 by naben-za          #+#    #+#             */
/*   Updated: 2022/06/01 13:12:17 by naben-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_finder(t_minishell *info, char *var, int *found)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->cp_envp[i])
	{
		if (ft_strncmp(info->cp_envp[i], var, ft_strlen(var))
			|| ft_strncmp(info->cp_envp[i] + ft_strlen(var), "=", 1))
			j++;
		else
			*found = 1;
		i++;
	}
	return (i);
}

int	unset_cpy(t_minishell *info, char *var, int *found, char **cpy_env)
{
	int		i;
	int		j;
	char	**cpyy_env;

	i = 0;
	j = 0;
	cpyy_env = cpy_env;
	while (info->cp_envp[i])
	{
		if (ft_strncmp(info->cp_envp[i], var, ft_strlen(var))
			|| ft_strncmp(info->cp_envp[i] + ft_strlen(var), "=", 1))
		{
			cpyy_env[j] = ft_strdup(info->cp_envp[i]);
			j++;
		}
		else
			*found = 1;
		i++;
	}
	cpy_env = cpyy_env;
	return (j);
}

void	unset_new_env(t_minishell *info, int *found, char **cpy_env, int j)
{
	char	**cpyy_env;

	cpyy_env = cpy_env;
	if (*found == 1)
	{
		cpyy_env[j] = NULL;
		free_tab(info->cp_envp);
		info->cp_envp = cpyy_env;
	}
	else
	{
		cpyy_env[j] = NULL;
		free_tab(cpyy_env);
	}
}

int	ft_unset2(t_minishell *info, char *var)
{
	char	**cpy_env;
	int		found;
	int		i;
	int		j;

	found = 0;
	if (info->cp_envp[0])
	{
		i = 0;
		i += unset_finder(info, var, &found);
		if (found == 1)
			cpy_env = malloc(sizeof(char *) * (i));
		else
			cpy_env = malloc(sizeof(char *) * (i + 1));
		if (!cpy_env)
			return (0);
		j = 0;
		j += unset_cpy(info, var, &found, cpy_env);
		unset_new_env(info, &found, cpy_env, j);
	}
	else
		info->cp_envp = NULL;
	g_exit_status = 0;
	return (1);
}

int	ft_unset(t_minishell *info, char *var)
{
	if (!var)
		return (0);
	if (ft_unset2(info, var) == 0)
		return (0);
	return (1);
}
