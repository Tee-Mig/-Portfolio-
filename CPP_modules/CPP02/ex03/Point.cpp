/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:03:34 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/28 14:50:43 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include "Fixed.hpp"

Point::Point():_x(Fixed(0)), _y(Fixed(0)) 
{
}

Point::Point(float const &nb1, float const &nb2): _x(Fixed(nb1)), _y(Fixed(nb2)) 
{
}

Point::~Point() {}

Point::Point(const Point &cp): _x(Fixed(cp._x)), _y(Fixed(cp._y)) 
{
	//std::cout << "Copy constructor called" << std::endl;
}

Point &Point::operator=(const Point &cp)
{
	(void)cp;
	return (*this);
}

float Point::getX() const
{
	return (this->_x.toFloat());
}

float Point::getY() const
{
	return (this->_y.toFloat());
}

std::ostream &operator<<(std::ostream &os, const Point &cp)
{
	os << "x = " << cp.getX() << std::endl;
	os << "y = " << cp.getY();
	return os;
}
