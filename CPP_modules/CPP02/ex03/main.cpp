/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:20:32 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/29 19:37:41 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

int main()
{
    Point a(1.0f, -1.0f);
    Point b(1.0f, 2.0f);
    Point c(-2.0f, -1.0f);

    Point p1(0.99, 1);
    Point p2(1.01, 1);
    Point p3(a);
    Point p4(0, 1);

    std::cout << bsp(a, b, c, p2) << std::endl;
    std::cout << bsp(a, b, c, p1) << std::endl;
    std::cout << bsp(a, b, c, p3) << std::endl;
    std::cout << bsp(a, b, c, p4) << std::endl;
    return 0;
}