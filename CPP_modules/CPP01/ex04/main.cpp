/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:29:17 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/20 17:16:45 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_replace_str.hpp"

int main(int ac, char **av)
{
	if (ac == 4)
		ft_replace_str(av[1], av[2], av[3]);
	else
		std::cout << "Error: number of argument" << std::endl;
	return 0;	
}