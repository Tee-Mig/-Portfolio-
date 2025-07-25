#include "Animal.hpp"

Animal::Animal(): _type("")
{
	std::cout << "Default Animal constructor" << std::endl;
}

Animal::Animal(std::string type): _type(type)
{
	std::cout << "Default Animal constructor with a type" << std::endl;
}

Animal::~Animal()
{
	std::cout << "Default Animal destructor" << std::endl;
}

Animal::Animal(const Animal &cp)
{
	std::cout << "Animal copy assignment" << std::endl;
	setType(cp._type);
}

Animal &Animal::operator=(const Animal &cp)
{
	std::cout << "Animal operator =" << std::endl;
	setType(cp._type);
	return (*this);
}

std::string Animal::getType() const
{
	return (this->_type);
}

void Animal::setType(std::string type)
{
	this->_type = type;
}