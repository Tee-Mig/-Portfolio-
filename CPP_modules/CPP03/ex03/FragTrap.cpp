/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:35:31 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/06 23:05:31 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name): ClapTrap(name, 100, 100, 30)
{
	std::cout << "FragTrap constructor 4 parameters called" << std::endl;
}

FragTrap::FragTrap(): ClapTrap()
{
	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &cp): ClapTrap(cp)
{
	std::cout << "FragTrap copy constructor" << std::endl;
	operator=(cp);
}

void FragTrap::attack(const std::string& target)
{
	if (this->getHitPoints() <= 0)
		std::cout << "FragTrap " << this->getName() << " is dead" << std::endl;
	else if (this->getEnergyPoints() == 0)
		std::cout << "FragTrap " << this->getName() << " has no more energy points" << std::endl;
	else
	{
		std::cout << "FragTrap " << this->getName() << " attacks " << target;
		std::cout << ", causing " << this->getAttackDamage() << " points of damage!" << std::endl;
		this->setEnergyPoints(this->getEnergyPoints() - 1);
	}
}

void FragTrap::highFivesGuys()
{
	if (this->getHitPoints() <= 0)
		std::cout << "ScavTrap " << this->getName() << " is dead and can't do an high fives" << std::endl;
	else if (this->getEnergyPoints() == 0)
		std::cout << "ScavTrap " << this->getName() << " has no more energy points and can't do an high fives" << std::endl;
	else
	{
		std::cout << "FragTrap " << this->getName() << " ask an high fives" << std::endl;
		this->setEnergyPoints(this->getEnergyPoints() - 1);
	}
}

void FragTrap::displayInfos()
{
	if (this->getHitPoints() > 0)
	{
		std::cout << "FragTrap " << this->getName() << " has " << this->getHitPoints() << " hit points, ";
		std::cout << this->getEnergyPoints() << " energy points and can inflict " << this->getAttackDamage();
		std::cout << " damage per hit" << std::endl;
	}
	else
	{
		std::cout << "FragTrap " << this->getName() << " is dead, he had ";
		std::cout << this->getEnergyPoints() << " energy points and could inflict " << this->getAttackDamage();
		std::cout << " damage per hit" << std::endl;
	}
}

// void FragTrap::setHitPoints(int hp)
// {
// 	this->setHitPoints(hp);
// }

// void FragTrap::setAttackDamage(int ad)
// {
// 	this->setAttackDamage(ad);
// }
