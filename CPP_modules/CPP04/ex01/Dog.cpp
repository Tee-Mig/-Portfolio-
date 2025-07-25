#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << "Default Dog constructor" << std::endl;
	this->_brain = new Brain();
}

Dog::~Dog()
{
	std::cout << "Default Dog destructor" << std::endl;
	delete this->_brain;
}

Dog::Dog(const Dog &cp)
{
	this->_brain = new Brain();
	std::cout << "Dog copy constructor" << std::endl;
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

void Dog::showBrain()
{
	this->_brain->showIdeas();
}
