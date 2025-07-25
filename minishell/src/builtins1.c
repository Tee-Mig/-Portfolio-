/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:39:00 by naben-za          #+#    #+#             */
/*   Updated: 2022/06/02 11:11:03 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo2(t_minishell *info, int i, int j)
{
	while (info->command[i].exec_array[j])
	{
		if (info->command[i].fd_out != -2)
			write(info->command[i].fd_out, info->command[i].exec_array[j],
				ft_strlen(info->command[i].exec_array[j]));
		else
			printf("%s", info->command[i].exec_array[j]);
		if (info->command[i].exec_array[j + 1] != NULL)
		{
			if (info->command[i].fd_out != -2)
				write(info->command[i].fd_out, " ", 1);
			else
				printf(" ");
		}
		j++;
	}
}

void	ft_echo(t_minishell *info, int i)
{
	int	j;
	int	opt;

	j = 1;
	opt = 0;
	if (info->command[i].exec_array[j])
	{
		if (!ft_strcmp(info->command[i].exec_array[1], "-n"))
		{
			opt = 1;
			j++;
		}
		ft_echo2(info, i, j);
	}
	if (opt == 0)
	{
		if (info->command[i].fd_out != -2)
			write(info->command[i].fd_out, "\n", 1);
		else
			printf("\n");
	}
	g_exit_status = 0;
}

int	update_oldpath(t_minishell *info)
{
	char	var_path[10000];
	char	*old_path;
	int		i;
	char	*char_tmp;

	i = 0;
	while (ft_strncmp(info->cp_envp[i], "OLDPWD", 6))
		i++;
	if (info->cp_envp[i] == NULL)
		return (0);
	if (!getcwd(var_path, 10000))
	{
		perror("Error");
		g_exit_status = 1;
		return (0);
	}
	old_path = ft_strdup("OLDPWD=");
	char_tmp = old_path;
	old_path = ft_strjoin_str(old_path, var_path);
	free(char_tmp);
	free(info->cp_envp[i]);
	info->cp_envp[i] = old_path;
	g_exit_status = 0;
	return (1);
}

void	ft_cd(t_minishell *info, int i)
{
	char	*path;
	int		ret;

	update_oldpath(info);
	path = info->command[i].exec_array[1];
	if (path == NULL)
	{
		write(1, "Need path abs or rel\n", ft_strlen("Need path abs or rel\n"));
		g_exit_status = 1;
	}
	else
	{
		ret = chdir(path);
		if (ret != 0)
		{	
			if (info->command[i].fd_out != -2)
				write(info->command[i].fd_out, "cd: No such file or directory\n",
					ft_strlen("cd: No such file or directory\n"));
			else
				printf("cd: No such file or directory\n");
			g_exit_status = 1;
		}
		else
			g_exit_status = 0;
	}
}
