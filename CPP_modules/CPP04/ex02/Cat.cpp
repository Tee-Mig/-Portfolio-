#include "Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << "Default Cat constructor" << std::endl;
	this->_brain = new Brain();
}

Cat::~Cat()
{
	std::cout << "Default Cat destructor" << std::endl;
	delete this->_brain;
}

Cat::Cat(const Cat &cp): Animal()
{
	this->_brain = new Brain();
	std::cout << "Default Cat copy assignment" << std::endl;
	setType(cp._type);
}

Cat &Cat::operator=(const Cat &cp)
{
	std::cout << "Cat operator =" << std::endl;
	setType(cp._type);
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << "Meoooooooow" << std::endl;
}

void Cat::showBrain()
{
	this->_brain->showIdeas();
}

