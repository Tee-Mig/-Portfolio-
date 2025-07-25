/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:27:54 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/06 17:17:41 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_H
#define CLAPTRAP_H

#include <iostream>

class ClapTrap
{
	protected:
		std::string _name;
		int			_hit_points;
		int			_energy_points;
		int			_attack_damage;
	public:
		ClapTrap();
		~ClapTrap();
		ClapTrap(std::string name, int hit_points, int energy_points, int attack_damage);
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap &cp);
		ClapTrap& operator=(const ClapTrap &cp);
		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
		void displayInfos();
		std::string getName();
		int getHitPoints();
		int getEnergyPoints();
		int getAttackDamage();
		void setName(std::string name);
		void setHitPoints(int hp);
		void setEnergyPoints(int ep);
		void setAttackDamage(int ad);
};

#endif