/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:41:13 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/29 19:35:53 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <stdio.h>

float sign(const Point a, const Point b, const Point c)
{
	float result;
	
	result = (a.getX() - c.getX()) * (b.getY() - c.getY()) - (b.getX() - c.getX()) * (a.getY() - c.getY());
	if (result < 0)
		result *= -1;
	return result;
} 

bool bsp(const Point a, const Point b, const Point c, const Point point)
{
	float sign1, sign2, sign3, abc;
	//std::cout << a.getX() << a.getY() << std::endl;
	sign1 = sign(point, a, b);
	//std::cout << "sign1 = " << sign1 << std::endl;
	sign2 = sign(point, b, c);
	//std::cout << "sign2 = " << sign2 << std::endl;
	sign3 = sign(point, c, a);
	//std::cout << "sign3 = " << sign3 << std::endl;
	abc = sign(a, b, c);

	if ((sign1 > 0 && sign2 > 0 && sign3 > 0) && abc == (sign1 + sign2 + sign3))
		return 1;
	return 0;
}
