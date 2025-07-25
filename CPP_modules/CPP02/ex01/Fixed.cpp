/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:38:36 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/29 19:20:35 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed():_nb(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &cp)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = cp;
}

Fixed& Fixed::operator=(const Fixed &cp)
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->setRawBits(cp.getRawBits());
	return *this;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
	return (this->_nb);
}

void Fixed::setRawBits(int const raw)
{
	this->_nb = raw;
}

float Fixed::toFloat(void) const
{
	return ((float)_nb) / (1 << this->_nb_bit);
}
int Fixed::toInt(void) const
{
	return ((int)this->_nb >> this->_nb_bit);
}

Fixed::Fixed(const int int_nb)
{
	this->_nb = int_nb << this->_nb_bit;
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float float_nb)
{
	this->_nb = roundf(float_nb * (1 << this->_nb_bit));
	std::cout << "Float constructor called" << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Fixed &cp)
{
	os << cp.toFloat();
	return os;
}