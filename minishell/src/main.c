/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:53:33 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/03 12:29:29 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned char	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_minishell	info;

	(void)ac;
	(void)av;
	if (ft_init(&info, envp) == 0)
		return (1);
	while (1)
	{
		if (ft_read_input(&info) == 0)
			break ;
		if (ft_strcmp(info.input, ""))
			info.input = ft_strtrim(info.input, "\n\t ");
		if (check_quote(info.input) == 0)
			printf("Error: quotes\n");
		else if (ft_strcmp(info.input, ""))
			if (if_input_valid(&info) == 0)
				break ;
		if (free_tokens(&info) == 0)
			break ;
	}
	free_end(&info);
	return (0);
}

int	init_cp_envp(t_minishell *info, char **envp)
{
	info->input = NULL;
	if (get_path_env(info, envp) == 0)
	{
		if (info->tokens)
			free(info->tokens);
		if (info->garbage_collector)
			free(info->garbage_collector);
		if (info->cp_envp)
			free_tab(info->cp_envp);
		if (info->path)
			free_tab(info->path);
		printf("Error: malloc\n");
		return (0);
	}
	return (1);
}

int	ft_init(t_minishell *info, char **envp)
{
	info->tokens = ft_lstnew();
	if (!info->tokens)
	{
		printf("Error: malloc\n");
		return (0);
	}
	info->garbage_collector = ft_lstnew();
	if (!info->garbage_collector)
	{
		if (info->tokens)
			free(info->tokens);
		printf("Error: malloc\n");
		return (0);
	}
	if (init_cp_envp(info, envp) == 0)
		return (0);
	g_exit_status = 0;
	return (1);
}
