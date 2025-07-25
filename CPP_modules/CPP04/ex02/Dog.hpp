#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain *_brain;
	public:
		Dog();
		virtual ~Dog();
		Dog(const Dog &cp);
		Dog &operator=(const Dog &cp);
		void makeSound() const;
		void showBrain();
};

#endif