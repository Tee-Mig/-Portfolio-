/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:29:55 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/15 16:54:51 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
	int	i = 0;

	Zombie *zombies = new Zombie[N];
	while (i < N)
	{
		zombies[i].setName(name);
		i++;
	}
	return (zombies);
}