/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:45:01 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/02 12:37:09 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_cpy_envp(char **envp)
{
	char	**cp_envp;
	int		i;

	i = 0;
	while (envp[i])
		++i;
	cp_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		cp_envp[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		cp_envp[i] = envp[i];
		i++;
	}
	envp[i] = NULL;
	return (cp_envp);
}

int	update_path(t_minishell *info)
{
	int	i;

	i = -1;
	if (info->path)
		free_tab(info->path);
	while (info->cp_envp[++i] && strncmp("PATH=", info->cp_envp[i], 5) != 0)
		;
	if (!info->cp_envp[i])
	{
		info->path = NULL;
		return (1);
	}
	info->path = ft_split(info->cp_envp[i] + 5, ":");
	if (!info->path)
	{
		printf("Error: malloc\n");
		return (0);
	}
	if (add_end_path(info, &i) == 0)
		return (0);
	return (1);
}

int	get_path_env(t_minishell *info, char **envp)
{
	int	i;

	info->path = NULL;
	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
		i++;
	info->cp_envp = malloc(sizeof(char *) * (i + 1));
	if (!info->cp_envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		info->cp_envp[i] = ft_strdup(envp[i]);
		if (!info->cp_envp)
			return (0);
		i++;
	}
	info->cp_envp[i] = NULL;
	if (get_path_env2(info, envp) == 0)
		return (0);
	return (1);
}

int	get_path_env2(t_minishell *info, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] && strncmp("PATH=", envp[i], 5) != 0)
		;
	if (!envp[i])
		return (1);
	info->path = ft_split(envp[i] + 5, ":");
	if (!info->path)
	{
		printf("Error: malloc\n");
		return (0);
	}
	if (add_end_path(info, &i) == 0)
		return (0);
	return (1);
}
