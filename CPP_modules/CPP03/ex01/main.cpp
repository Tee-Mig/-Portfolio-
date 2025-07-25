/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:50:09 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/06 22:55:10 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
	ScavTrap perso1("Jean pierre");

	perso1.displayInfos();
	perso1.attack("bernard");
	perso1.takeDamage(10);
	perso1.guardGate();
	perso1.takeDamage(10);
	perso1.guardGate();
	perso1.attack("JPP");
	perso1.beRepaired(10);
	perso1.displayInfos();
	perso1.takeDamage(100);
	perso1.guardGate();
	perso1.attack("JPP");
	perso1.beRepaired(10);
	return 0;
}