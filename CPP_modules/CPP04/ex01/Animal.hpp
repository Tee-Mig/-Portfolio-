#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal
{
	protected:
		std::string _type;
	public:
		Animal();
		virtual ~Animal();
		Animal(std::string type);
		Animal(const Animal &cp);
		Animal& operator=(const Animal &cp);
		std::string getType() const;
		void setType(std::string type);
		virtual void makeSound() const;
};

#endif
