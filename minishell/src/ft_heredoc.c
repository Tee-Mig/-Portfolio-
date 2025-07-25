/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:15:14 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/01 16:36:35 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(char *delimiter)
{
	char	*line;
	int		tmp;

	tmp = open("tmp5684624", O_CREAT | O_RDWR | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	line = readline("");
	while (ft_strcmp(line, delimiter))
	{
		if (!line)
			break ;
		write(tmp, line, ft_strlen(line));
		write(tmp, "\n", 1);
		free(line);
		line = readline("");
	}
	free(line);
	close(tmp);
	tmp = open("tmp5684624", O_RDONLY);
	return (tmp);
}
