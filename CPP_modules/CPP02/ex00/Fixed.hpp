/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:03:55 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/29 18:55:30 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
	private:
		float				_nb;
		const static int	_nb_bit = 8;
	public:
		Fixed();
		Fixed(const Fixed &cp);
		Fixed& operator=(const Fixed &cp);
		~Fixed();
		int getRawBits(void) const;
		void setRawBits(int const raw);
};

#endif