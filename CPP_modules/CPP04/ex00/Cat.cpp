#include "Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << "Default Cat constructor" << std::endl;
}

Cat::~Cat()
{
	std::cout << "Default Cat destructor" << std::endl;
}

Cat::Cat(const Cat &cp): Animal()
{
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
