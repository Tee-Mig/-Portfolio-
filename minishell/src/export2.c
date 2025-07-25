/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:35:37 by naben-za          #+#    #+#             */
/*   Updated: 2022/06/03 12:53:57 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_syntax(t_minishell *info, char *var, int id, int *j)
{
	info->command[id].plus_status = 0;
	while (var[*j] && var[*j] != '=')
	{
		if (var[*j] == '+')
			info->command[id].plus_status++;
		if (ft_isalnum(var[*j]) == 0 || info->command[id].plus_status > 1)
		{
			g_exit_status = 2;
			if (info->command[id].fd_out != -2)
				write(info->command[id].fd_out, "Error: syntax\n",
					ft_strlen("Error: syntax\n"));
			else
				printf("Error: syntax\n");
			return (0);
		}
		else
			*j += 1;
	}
	return (1);
}

int	export_identifier_envp(t_minishell *info, char *var, int id, int j)
{
	if (var[0] == '+' && j == 1)
	{
		if (info->command[id].fd_out != -2)
			write(info->command[id].fd_out, "Error: not a valid identifier\n",
				ft_strlen("Error: not a valid identifier\n"));
		else
			printf("Error: not a valid identifier\n");
		g_exit_status = 1;
		return (0);
	}
	if (var[j] == '\0')
	{
		g_exit_status = 1;
		return (0);
	}
	if (!info->cp_envp[0])
	{
		g_exit_status = 1;
		return (0);
	}
	return (1);
}

void	export_nofindvar2(t_minishell *info, char *var, int id, char **cpy_env)
{
	int	j;
	int	k;

	j = 0;
	while (info->cp_envp[j])
	{
		cpy_env[j] = ft_strdup(info->cp_envp[j]);
		j++;
	}
	if (info->command[id].plus_status != 1)
		cpy_env[j] = ft_strdup(var);
	else
	{
		k = 0;
		cpy_env[j] = ft_strdup("");
		while (var[k])
		{
			if (var[k] != '+' || info->command[id].plus_status != 1)
				cpy_env[j] = ft_strjoin(cpy_env[j], var[k]);
			else
				info->command[id].plus_status--;
			k++;
		}
	}
	cpy_env[j + 1] = 0;
}

int	export_nofindvar1(t_minishell *info, char *var, int id, int i)
{
	char	**cpy_env;

	cpy_env = malloc(sizeof(char *) * (i + 2));
	if (!cpy_env)
		return (0);
	export_nofindvar2(info, var, id, cpy_env);
	free_tab(info->cp_envp);
	info->cp_envp = cpy_env;
	return (1);
}

void	export_findvar(t_minishell *info, char *var, int id, int j)
{
	if (info->command[id].plus_status == 1)
	{
		j++;
		while (var[j])
		{
			info->cp_envp[info->command[id].find_var]
				= ft_strjoin(info->cp_envp[info->command[id].find_var], var[j]);
			j++;
		}
	}
	else
	{
		free(info->cp_envp[info->command[id].find_var]);
		info->cp_envp[info->command[id].find_var] = ft_strdup(var);
	}
}
