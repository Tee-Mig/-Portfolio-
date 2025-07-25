/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:50:09 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/07 12:00:45 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main()
{
	DiamondTrap perso2("Mig");

	perso2.displayInfos();
	perso2.attack("bernard");
	perso2.guardGate();
	perso2.highFivesGuys();
	perso2.whoAmI();
	perso2.takeDamage(150);
	perso2.highFivesGuys();
	perso2.whoAmI();
	perso2.guardGate();
	perso2.displayInfos();
	return 0;
}