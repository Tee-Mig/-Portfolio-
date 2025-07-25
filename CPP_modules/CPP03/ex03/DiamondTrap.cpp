/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:12:35 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/07 10:39:59 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(): ClapTrap("_clap_name", 100, 50, 30), FragTrap(), ScavTrap()
{
	this->_name = "_clap_name";
	std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap default destructor called" << std::endl;
}

void DiamondTrap::attack(const std::string &target)
{
	ScavTrap::attack(target);
}

DiamondTrap::DiamondTrap(const DiamondTrap &cp): ClapTrap(this->getName()), FragTrap(cp), ScavTrap(cp)
{
	std::cout << "DiamondTrap copy constructor" << std::endl;
	operator=(cp);
}

DiamondTrap::DiamondTrap(std::string name): ClapTrap(name + "_clap_name", 100, 50, 30), FragTrap(), ScavTrap()
{
	this->_name = name;
	std::cout << "DiamondTrap constructor 4 parameters called" << std::endl;
}

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap's name is " << this->_name << " and his sub objet name is " << this->getName() << std::endl;
}

void DiamondTrap::displayInfos()
{
	if (this->getHitPoints() > 0)
	{
		std::cout << "DiamondTrap " << this->_name << " has " << this->getHitPoints() << " hit points, ";
		std::cout << this->getEnergyPoints() << " energy points and can inflict " << this->getAttackDamage();
		std::cout << " damage per hit" << std::endl;
	}
	else
	{
		std::cout << "DiamondTrap " << this->getName() << " is dead, he had ";
		std::cout << this->getEnergyPoints() << " energy points and could inflict " << this->getAttackDamage();
		std::cout << " damage per hit" << std::endl;
	}
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& cp)
{
	std::cout << "DiamondTrap operator =" << std::endl;
	ClapTrap::operator=(cp);
	this->_name = cp._name;
	return *this;
}
