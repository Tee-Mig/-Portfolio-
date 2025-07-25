/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:50:09 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/07 11:56:17 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
	ClapTrap character1("Mig");
	character1.displayInfos();
	character1.beRepaired(11);
	character1.displayInfos();
	character1.takeDamage(13);
	character1.displayInfos();
	character1.takeDamage(10);
	character1.displayInfos();
	character1.attack("Jean pierre");
	character1.beRepaired(20);
	return 0;
}