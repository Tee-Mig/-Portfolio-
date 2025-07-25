/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bleed_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 03:39:10 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/22 05:10:22 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	bleed_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
		(free(line), line = get_next_line(fd));
	close(fd);
}
