#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal
{
	public:
		Cat();
		~Cat();
		Cat(const Cat &cp);
		Cat &operator=(const Cat &cp);
		void makeSound() const;
};

#endif