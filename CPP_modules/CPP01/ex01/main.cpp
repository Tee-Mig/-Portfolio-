/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:32:59 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/21 11:39:42 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
const int nb_zombie = 2;

int main()
{
	int i = 0;
	Zombie *zombies1 = zombieHorde(nb_zombie, "miguelito");
	Zombie *zombies2 = zombieHorde(nb_zombie + 5, "pepito");
	while (i < nb_zombie)
	{
		zombies1[i].announce();
		i++;
	}
	i = 0;
	while (i < nb_zombie + 5)
	{
		zombies2[i].announce();
		i++;
	}
	delete [] zombies1;
	delete [] zombies2;
	return 0;
}