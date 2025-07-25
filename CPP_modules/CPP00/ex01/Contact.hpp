/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 00:00:32 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/28 23:48:05 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact
{
	private:
		std::string _first_name;
		std::string _last_name;
		std::string _nickname;
		std::string _phone_number;
		std::string _darkest_secret;
	public:
		void set_first_name(std::string);
		void set_last_name(std::string);
		void set_nickname(std::string);
		void set_phone_number(std::string);
		void set_darkest_secret(std::string);
		std::string const get_first_name();
		std::string const get_last_name();
		std::string const get_nickname();
		std::string const get_phone_number();
		std::string const get_darkest_secret();
};

#endif