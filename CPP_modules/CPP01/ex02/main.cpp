/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:33 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/17 15:57:30 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main()
{
	std::string var_str = "HI THIS IS BRAIN";
	std::string *stringPTR = &var_str;
	std::string &stringREF = var_str;

	std::cout << "memory address of var_str = " << &var_str << std::endl;
	std::cout << "memory address of stringPTR = " << stringPTR << std::endl;
	std::cout << "memory address of stringREF = " << &stringREF << "\n" << std::endl;

	std::cout << "value pointed by var_str = " << var_str << std::endl;
	std::cout << "value pointed by stringPTR = " << *stringPTR << std::endl;
	std::cout << "value pointed by stringREF = " << stringREF << std::endl;
}