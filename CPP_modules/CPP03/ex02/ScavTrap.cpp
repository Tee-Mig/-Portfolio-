/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:49:13 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/06 22:55:43 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name): ClapTrap(name, 100, 50, 20)
{
	std::cout << "ScavTrap constructor 4 paramaters called" << std::endl;
}

ScavTrap::ScavTrap(): ClapTrap()
{
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &cp): ClapTrap()
{
	std::cout << "ScavTrap copy constructor" << std::endl;
	operator=(cp);
}

void ScavTrap::attack(const std::string& target)
{
	if (this->getHitPoints() <= 0)
		std::cout << "ScavTrap " << this->getName() << " is dead and can't attack" << std::endl;
	else if (this->getEnergyPoints() == 0)
		std::cout << "ScavTrap " << this->getName() << " has no more energy points" << std::endl;
	else
	{
		std::cout << "ScavTrap " << this->getName() << " attacks " << target;
		std::cout << ", causing " << this->getAttackDamage() << " points of damage!" << std::endl;
		this->setEnergyPoints(this->getEnergyPoints() - 1);
	}
}

void ScavTrap::guardGate()
{
	if (this->getHitPoints() <= 0)
		std::cout << "ScavTrap " << this->getName() << " is dead and can't enter in Gate keeper mode" << std::endl;
	else if (this->getEnergyPoints() == 0)
		std::cout << "ScavTrap " << this->getName() << " has no more energy points and can't enter in Gate keeper mode" << std::endl;
	else
	{
		std::cout << "ScavTrap " << this->getName() << " entered in Gate keeper mode" << std::endl;
		this->setEnergyPoints(this->getEnergyPoints() - 1);
	}
}

void ScavTrap::displayInfos()
{
	if (this->getHitPoints() > 0)
	{
		std::cout << "ScavTrap " << this->getName() << " has " << this->getHitPoints() << " hit points, ";
		std::cout << this->getEnergyPoints() << " energy points and can inflict " << this->getAttackDamage();
		std::cout << " damage per hit" << std::endl;
	}
	else
	{
		std::cout << "ScavTrap " << this->getName() << " is dead, he had ";
		std::cout << this->getEnergyPoints() << " energy points and could inflict " << this->getAttackDamage();
		std::cout << " damage per hit" << std::endl;
	}
}
