#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain *_brain;
	public:
		Cat();
		virtual ~Cat();
		Cat(const Cat &cp);
		Cat &operator=(const Cat &cp);
		void makeSound() const;
		void showBrain();
};

#endif