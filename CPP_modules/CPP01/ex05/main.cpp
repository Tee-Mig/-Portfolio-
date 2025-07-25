/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:58:34 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/27 11:35:15 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int ac, char **av)
{
	(void)ac;
	Harl karen;
	if (ac == 2)
		karen.complain(av[1]);
	else
		std::cout << "Karen needs 2 arguments to complain" << std::endl;
	return 0;
}