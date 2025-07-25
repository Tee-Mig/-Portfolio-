/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:26:13 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/17 18:24:49 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "Contact.hpp"

class PhoneBook
{
	private:
		int i;
		int	nb_user;
		std::string	input_id;
		void add_user();
		void search_user();
		Contact contacts[8];
	public:
		PhoneBook();
		void check_arg(std::string input);

};

#endif