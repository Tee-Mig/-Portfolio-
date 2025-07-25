/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:50:09 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/07/07 11:58:50 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
	FragTrap character3("Bernard");
	character3.displayInfos();
	character3.takeDamage(15);
	character3.attack("Marcel");
	character3.highFivesGuys();
	character3.takeDamage(230);
	character3.attack("Marcel");
	character3.highFivesGuys();
	character3.displayInfos();
	
	return 0;
}