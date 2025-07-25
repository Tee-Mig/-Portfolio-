/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 20:25:47 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/23 14:13:02 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac == 5)
	{
		if (ft_parsing(av))
			ft_process(av, envp);
		else
			ft_putstr("Error: open\n");
	}
	else
		ft_putstr("Error: arguments\n");
	return (0);
}
