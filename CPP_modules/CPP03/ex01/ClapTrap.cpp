/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:33:54 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/06 15:22:33 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name): 
	_name(name), _hit_points(10), _energy_points(10), _attack_damage(0)
{
	std::cout << "ClapTrap constructor 1 parameter called" << std::endl;
}

ClapTrap::ClapTrap(std::string name, int hit_points, int energy_points, int attack_damage): 
	_name(name), _hit_points(hit_points), _energy_points(energy_points), _attack_damage(attack_damage)
{
	std::cout << "ClapTrap constructor 4 parameters called" << std::endl;
}

ClapTrap::ClapTrap(): 
	_name(""), _hit_points(10), _energy_points(10), _attack_damage(0)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap destructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &cp)
{
	std::cout << "ClapTrap copy constructor" << std::endl;
	this->_attack_damage = cp._attack_damage;
	this->_energy_points = cp._energy_points;
	this->_hit_points = cp._hit_points;
	this->_name = cp._name;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &cp)
{
	std::cout << "Operator =" << std::endl;
	this->_attack_damage = cp._attack_damage;
	this->_energy_points = cp._energy_points;
	this->_hit_points = cp._hit_points;
	this->_name = cp._name;
	return (*this);
}

void ClapTrap::attack(const std::string& target)
{
	if (this->_hit_points <= 0)
		std::cout << "ClapTrap " << this->_name << " is dead and can't attack" << std::endl;
	else if (this->_energy_points == 0)
		std::cout << "ClapTrap " << this->_name << " has no more energy points" << std::endl;
	else
	{
		std::cout << "ClapTrap " << this->_name << " attacks " << target;
		std::cout << ", causing " << this->_attack_damage << " points of damage!" << std::endl;
		this->_energy_points--;
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hit_points <= 0)
		std::cout << "ClapTrap " << this->_name << " is already dead and can't take damage" << std::endl;
	else
	{
		std::cout << "ClapTrap " << this->_name << " takes " << amount;
		std::cout << " points of damage!" << std::endl;
		this->_hit_points-= amount;
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_hit_points <= 0)
		std::cout << "ClapTrap " << this->_name << " is dead and can't be repaired" << std::endl;
	else if (this->_energy_points == 0)
		std::cout << "ClapTrap " << this->_name << " has no more energy points" << std::endl;
	else
	{
		std::cout << "ClapTrap " << this->_name << " uses his abilitie and recovers " << amount;
		std::cout << " hit points " << std::endl;
		this->_energy_points--;
		this->_hit_points+= amount;
	}
}

void ClapTrap::displayInfos()
{
	if (this->_hit_points > 0)
	{
		std::cout << "ClapTrap " << this->_name << " has " << this->_hit_points << " hit points, ";
		std::cout << this->_energy_points << " energy points and can inflict " << this->_attack_damage;
		std::cout << " damage per hit" << std::endl;
	}
	else
	{
		std::cout << "ClapTrap " << this->getName() << " is dead, he had ";
		std::cout << this->_energy_points << " energy points and could inflict " << this->_attack_damage;
		std::cout << " damage per hit" << std::endl;
	}
}

std::string ClapTrap::getName()
{
	return (this->_name);
}

int ClapTrap::getHitPoints()
{
	return (this->_hit_points);
}

int ClapTrap::getEnergyPoints()
{
	return (this->_energy_points);
}

int ClapTrap::getAttackDamage()
{
	return (this->_attack_damage);
}

void ClapTrap::setName(std::string name)
{
	this->_name = name;
}

void ClapTrap::setHitPoints(int hp)
{
	this->_hit_points = hp;
}

void ClapTrap::setEnergyPoints(int ep)
{
	this->_energy_points = ep;
}

void ClapTrap::setAttackDamage(int ad)
{
	this->_attack_damage = ad;
}
