/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:54:03 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/17 18:26:14 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void Contact::set_first_name(std::string first_name)
{
	this->_first_name = first_name;
}

void Contact::set_last_name(std::string last_name)
{
	this->_last_name = last_name;
}

void Contact::set_nickname(std::string nickname)
{
	this->_nickname = nickname;
}

void Contact::set_phone_number(std::string phone_number)
{
	this->_phone_number = phone_number;
}

void Contact::set_darkest_secret(std::string darkest_secret)
{
	this->_darkest_secret = darkest_secret;
}

std::string const Contact::get_first_name()
{
	return _first_name;
}

std::string const Contact::get_last_name()
{
	return _last_name;
}

std::string const Contact::get_nickname()
{
	return _nickname;
}

std::string const Contact::get_phone_number()
{
	return _phone_number;
}

std::string const Contact::get_darkest_secret()
{
	return _darkest_secret;
}
