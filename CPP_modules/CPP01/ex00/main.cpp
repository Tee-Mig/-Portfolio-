/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:52:41 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/21 11:36:17 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
	Zombie *zombie1_heap = newZombie("miguel_heap");
	Zombie zombie_stack("jean_stack");
	zombie1_heap->announce();
	zombie1_heap->announce();
	zombie_stack.announce();
	randomChump("bernard_chump");
	delete zombie1_heap;
	return 0;
}