/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:36:23 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/17 15:45:21 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_parsing(char **av)
{
	int		fd1;
	int		fd2;

	if (access(av[4], 0) == -1)
	{
		fd1 = open(av[4], O_CREAT | O_RDONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd1 == -1)
			return (0);
		close(fd1);
	}
	if (access(av[1], 0) == -1)
	{
		fd2 = open(av[4], O_RDWR | O_TRUNC);
		if (fd2 == -1)
			return (0);
		close(fd2);
	}
	return (1);
}
