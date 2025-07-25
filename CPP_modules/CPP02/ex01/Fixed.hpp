/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:15:50 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/25 16:44:28 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <math.h>

class Fixed
{
	private:
		float				_nb;
		const static int	_nb_bit = 8;
	public:
		Fixed();
		~Fixed();
		Fixed(const int int_nb);
		Fixed(const float float_nb);
		Fixed(const Fixed& cp);
		Fixed& operator=(const Fixed &cp);
		float toFloat(void) const;
		int toInt(void) const;
		int getRawBits(void) const;
		void setRawBits(int const raw);
};

std::ostream &operator<<(std::ostream &os, const Fixed &cp);

#endif