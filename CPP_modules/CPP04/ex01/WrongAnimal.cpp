#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(): _type("")
{
	std::cout << "Default WrongAnimal constructor" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type): _type(type)
{
	std::cout << "Default WrongAnimal constructor with a type" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "Default WrongAnimal destructor" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &cp)
{
	std::cout << "WrongAnimal copy assignment" << std::endl;
	setType(cp._type);
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &cp)
{
	std::cout << "WrongAnimal operator =" << std::endl;
	setType(cp._type);
	return (*this);
}

std::string WrongAnimal::getType() const
{
	return (this->_type);
}

void WrongAnimal::setType(std::string type)
{
	this->_type = type;
}

void WrongAnimal::makeSound() const
{
	std::cout << "WrongAnimal soooooooooooooooooooooound" << std::endl;
}