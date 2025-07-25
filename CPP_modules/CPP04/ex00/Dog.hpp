#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal
{
	public:
		Dog();
		~Dog();
		Dog(const Dog &cp);
		Dog &operator=(const Dog &cp);
		void makeSound() const;
};

#endif