/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:43:08 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/20 18:44:39 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "Weapon.hpp"

HumanA::HumanA(std::string name, Weapon &weapon): _weapon(weapon)
{
	this->_name = name;
	std::cout << this->_name << " appears with " << this->_weapon.getType() << std::endl;
}

void HumanA::attack()
{
		std::cout << this->_name << " attacks with their " << this->_weapon.getType() << std::endl;
}
