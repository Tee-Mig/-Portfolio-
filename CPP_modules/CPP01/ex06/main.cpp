/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:20:59 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/27 11:35:29 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int ac, char **av)
{
	Harl karen;
	if (ac == 2)
		karen.harlFilter(av[1]);
	else
		std::cout << "Karen needs 2 arguments to complain" << std::endl;
	return 0;
}