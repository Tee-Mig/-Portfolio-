/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:38:36 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/29 19:34:39 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed():_nb(0)
{
}

Fixed::Fixed(const Fixed &cp)
{
	*this = cp;
}

Fixed& Fixed::operator=(const Fixed &cp)
{
	this->setRawBits(cp.getRawBits());
	return *this;
}

Fixed::~Fixed()
{
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
}

Fixed::Fixed(const float float_nb)
{
	this->_nb = roundf(float_nb * (1 << this->_nb_bit));
}

std::ostream &operator<<(std::ostream &os, const Fixed &cp)
{
	os << cp.toFloat();
	return os;
}

bool Fixed::operator>(const Fixed &cp)
{
	if (this->getRawBits() > cp.getRawBits())
		return 1;
	else
		return 0;
}

bool Fixed::operator<(const Fixed &cp)
{
	if (this->getRawBits() < cp.getRawBits())
		return 1;
	else
		return 0;
}

bool Fixed::operator>=(const Fixed &cp)
{
	if (this->getRawBits() >= cp.getRawBits())
		return 1;
	else
		return 0;
}

bool Fixed::operator<=(const Fixed &cp)
{
	if (this->getRawBits() <= cp.getRawBits())
		return 1;
	else
		return 0;
}

bool Fixed::operator==(const Fixed &cp)
{
	if (this->getRawBits() == cp.getRawBits())
		return 1;
	else
		return 0;
}

bool Fixed::operator!=(const Fixed &cp)
{
	if (this->getRawBits() != cp.getRawBits())
		return 1;
	else
		return 0;
}

Fixed Fixed::operator+(const Fixed &cp)
{
	this->_nb = this->toFloat() + cp.toFloat();
	return (_nb);
}

Fixed Fixed::operator-(const Fixed &cp)
{
	this->_nb = this->toFloat() - cp.toFloat();
	return (_nb);
}

Fixed Fixed::operator*(const Fixed &cp)
{
	this->_nb = this->toFloat() * cp.toFloat();
	return (_nb);
}

Fixed Fixed::operator/(const Fixed &cp)
{
	this->_nb = this->toFloat() / cp.toFloat();
	return (_nb);
}

Fixed Fixed::operator++(int)
{
	Fixed tmp = *this;
	++(this->_nb);
	return tmp;

}
Fixed &Fixed::operator++(void)
{
	++(this->_nb);
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed tmp = *this;
	--(this->_nb);
	return tmp;
}

Fixed &Fixed::operator--(void)
{
	this->_nb--;
	return *this;
}

Fixed &Fixed::min(Fixed &nb1, Fixed &nb2)
{
	if (nb1.getRawBits() < nb2.getRawBits())
		return (nb1);
	else
		return (nb2);
}

const Fixed &Fixed::min(const Fixed &nb1, const Fixed &nb2)
{
	if (nb1.getRawBits() < nb2.getRawBits())
		return (nb1);
	else
		return (nb2);
}

Fixed &Fixed::max(Fixed &nb1, Fixed &nb2)
{
	if (nb1.getRawBits() > nb2.getRawBits())
		return (nb1);
	else
		return (nb2);
}

const Fixed &Fixed::max(const Fixed &nb1, const Fixed &nb2)
{
	if (nb1.getRawBits() > nb2.getRawBits())
		return (nb1);
	else
		return (nb2);
}
