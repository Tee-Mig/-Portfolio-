/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:28:54 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/20 16:07:10 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"

PhoneBook::PhoneBook()
{
	i = 0;
	nb_user = 0;
}

void PhoneBook::search_user()
{
	int j = 0;

	std::cout << std::setw(10) << "id" << "|" << std::setw(10) << "first name" << "|";
	std::cout << std::setw(10) << "last name" << "|" << std::setw(10) << "nickname";
	std::cout << std::endl;
	std::cout << std::string(48, '-') << std::endl;
	while (j < nb_user)
	{
		std::cout << std::setw(10) << j << "|";

		if (contacts[j].get_first_name().size() <= 10)
			std::cout << std::setw(10) << contacts[j].get_first_name() << "|";
		else
			std::cout << contacts[j].get_first_name().substr(0, 9) << "." << "|";
		
		if (contacts[j].get_last_name().size() <= 10)
			std::cout << std::setw(10) << contacts[j].get_last_name() << "|";
		else
			std::cout << contacts[j].get_last_name().substr(0, 9) << "." << "|";
		
		if (contacts[j].get_nickname().size() <= 10)
			std::cout << std::setw(10) << contacts[j].get_nickname();
		else
			std::cout << contacts[j].get_nickname().substr(0, 9) << ".";
		j++;
		std::cout << std::endl;
	}
	std::cout << "Entrez l'index du contact a afficher: ";
	getline(std::cin, input_id);
	if (std::cin.eof())
		return ;
	if (nb_user > 0 && atoi(input_id.c_str()) >= 0 && atoi(input_id.c_str()) < nb_user)
	{
		if (atoi(input_id.c_str()) == 0 && (input_id[0] != '0' || input_id.size() > 1))
			std::cout << "Error: invalid index " << std::endl;	
		else
		{
			std::cout << "first name: " << contacts[atoi(input_id.c_str())].get_first_name() << std::endl;
			std::cout << "last name: " << contacts[atoi(input_id.c_str())].get_last_name() << std::endl;
			std::cout << "nickname: " << contacts[atoi(input_id.c_str())].get_nickname() << std::endl;
			std::cout << "phone number: " << contacts[atoi(input_id.c_str())].get_phone_number() << std::endl;
			std::cout << "darkest secret: " << contacts[atoi(input_id.c_str())].get_darkest_secret() << std::endl;
		}
	}
	else
		std::cout << "Error: invalid index" << std::endl;
}

void PhoneBook::add_user()
{
	std::string input;

	if (i > 7)
		i = 0;
	do
	{
		std::cout << "first name: ";
		getline(std::cin, input);
		if (std::cin.eof())
			return ;
	}while (input.empty());
	contacts[i].set_first_name(input);
	do
	{
		std::cout << "last name: ";
		getline(std::cin, input);
		if (std::cin.eof())
			return ;
	}while (input.empty());
	contacts[i].set_last_name(input);
	do
	{
		std::cout << "nickname: ";
		getline(std::cin, input);
		if (std::cin.eof())
			return ;
	}while (input.empty());
	contacts[i].set_nickname(input);
	do
	{
		std::cout << "phone number: ";
		getline(std::cin, input);
		if (std::cin.eof())
			return ;
	}while (input.empty());
	contacts[i].set_phone_number(input);
	do
	{
		std::cout << "darkest secret: ";
		getline(std::cin, input);
		if (std::cin.eof())
			return ;
	}while (input.empty());
	contacts[i].set_darkest_secret(input);
	i++;
	nb_user++;
	if (nb_user > 8)
		nb_user--;
}

void PhoneBook::check_arg(std::string input)
{
	if (input == "ADD")
		add_user();
	else if (input == "SEARCH")
		search_user();
}