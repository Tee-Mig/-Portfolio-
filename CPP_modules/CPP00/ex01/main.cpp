/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:25:46 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/17 14:08:54 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"

int main(int ac, char **av)
{
	(void)av;
	PhoneBook	repertoire;
	std::string	input;

	if (ac == 1)
	{
		std::cout << "Bienvenue dans le PhoneBook" << std::endl;
		while (true)
		{
			std::cout << "3 commandes possibles parmi ADD, SEARCH et EXIT: ";
			getline(std::cin, input);
			repertoire.check_arg(input);
			if (!std::cin || input == "EXIT")
				break ;
		}
		if (!std::cin)
			std::cout << std::endl;
		std::cout << "Au revoir et a bientot :p" << std::endl;
	}
	else
		std::cout << "Error: number of argument" << std::endl;

	return 0;
}