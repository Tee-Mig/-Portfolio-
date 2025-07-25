#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>

class WrongAnimal
{
	protected:
		std::string _type;
	public:
		WrongAnimal();
		virtual ~WrongAnimal();
		WrongAnimal(std::string type);
		WrongAnimal(const WrongAnimal &cp);
		WrongAnimal& operator=(const WrongAnimal &cp);
		std::string getType() const;
		void setType(std::string type);
		void makeSound() const;
};

#endif
