#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << "Default Dog constructor" << std::endl;
}

Dog::~Dog()
{
	std::cout << "Default Dog destructor" << std::endl;
}

Dog::Dog(const Dog &cp): Animal()
{
	std::cout << "Default Dog copy assignment" << std::endl;
	setType(cp._type);
}

Dog &Dog::operator=(const Dog &cp)
{
	std::cout << "Dog operator =" << std::endl;
	setType(cp._type);
	return (*this);
}

void Dog::makeSound() const
{
	std::cout << "wouaaaaaaaaaaf" << std::endl;
}
