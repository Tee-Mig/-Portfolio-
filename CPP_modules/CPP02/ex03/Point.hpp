/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:29:32 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/28 14:42:54 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point
{
	private:
		Fixed const _x;
		Fixed const _y;
		Point &operator=(const Point &cp);
	public:
		Point();
		~Point();
		Point(float const &nb1, float const &nb2);
		Point(const Point &cp);
		float getX() const;
		float getY() const;
};

float sign(const Point a, const Point b, const Point c);
std::ostream &operator<<(std::ostream &os, const Point &cp);
bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif