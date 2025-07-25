/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:36:23 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 15:01:46 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *file, char status)
{
	int	fd;

	fd = -1;
	if (status == 'h')
	{
		fd = open(file, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else if (status == 'i')
	{
		fd = open(file, O_CREAT | O_RDONLY);
	}
	else if (status == 'o')
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	return (fd);
}
