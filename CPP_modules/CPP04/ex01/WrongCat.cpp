#include "WrongCat.hpp"

WrongCat::WrongCat(): WrongAnimal("WrongCat")
{
	std::cout << "Default WrongCat constructor" << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "Default WrongCat destructor" << std::endl;
}

WrongCat::WrongCat(const WrongCat &cp): WrongAnimal()
{
	std::cout << "Default WrongCat copy assignment" << std::endl;
	setType(cp._type);
}

WrongCat &WrongCat::operator=(const WrongCat &cp)
{
	std::cout << "WrongCat operator =" << std::endl;
	setType(cp._type);
	return (*this);
}

void WrongCat::makeSound() const
{
	std::cout << "Pas de meow :c" << std::endl;
}
