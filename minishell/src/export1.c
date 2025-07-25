/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:35:26 by naben-za          #+#    #+#             */
/*   Updated: 2022/06/03 13:01:42 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var(t_minishell *info, char *var, int id, int j)
{
	int	i;

	i = 0;
	info->command[id].find_var = -1;
	while (info->cp_envp[i])
	{
		if (!ft_strncmp(var, info->cp_envp[i],
				j - info->command[id].plus_status))
			info->command[id].find_var = i;
		++i;
	}
	return (i);
}

int	export_noarg(t_minishell *info, char *var, int id)
{
	if (!var)
	{
		ft_env(info, id, 1);
		return (0);
	}
	return (1);
}

int	export_syn_id(t_minishell *info, char *var, int id, int *j)
{
	if (export_syntax(info, var, id, j) == 0)
		return (0);
	if (export_identifier_envp(info, var, id, *j) == 0)
		return (0);
	return (1);
}

int	ft_export(t_minishell *info, char *var, int id)
{
	int		i;
	int		j;

	if (export_noarg(info, var, 1) == 0)
		return (0);
	j = 0;
	if (export_syn_id(info, var, id, &j) == 0)
		return (0);
	if (info->cp_envp[0])
	{
		i = 0;
		i += check_var(info, var, id, j);
		if (info->command[id].find_var == -1)
		{
			if (export_nofindvar1(info, var, id, i) == 0)
				return (0);
		}
		else
			export_findvar(info, var, id, j);
		g_exit_status = 0;
	}
	else
		g_exit_status = 1;
	return (1);
}
