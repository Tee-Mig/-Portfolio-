#include "Type.hpp"

Base * generate(void)
{
	int value;
	srand (time(NULL));
	value = rand() % 3;
	if (value == 0)
		return (new A());
	else if (value == 1)
		return (new B());
	return (new C());	
}

void identify(Base* p)
{
	std::cout << "pointer identify" << std::endl;
	Base *test_cast;

	test_cast = dynamic_cast<A*>(p);
	if (test_cast != NULL)
		std::cout << "La Base est de type A" << std::endl;
	test_cast = dynamic_cast<B*>(p);
	if (test_cast != NULL)
		std::cout << "La Base est de type B" << std::endl;
	test_cast = dynamic_cast<C*>(p);
	if (test_cast != NULL)
		std::cout << "La Base est de type C" << std::endl;
}

void identify(Base& p)
{
	std::cout << "reference identify" << std::endl;
	try
	{
		p = dynamic_cast<A &>(p);
		std::cout << "La Base est de type A" << std::endl;
	}
	catch(...)
	{
	}

	try
	{
		p = dynamic_cast<B &>(p);
		std::cout << "La Base est de type B" << std::endl;
	}
	catch(...)
	{
	}

	try
	{
		p = dynamic_cast<C &>(p);
		std::cout << "La Base est de type C" << std::endl;
	}
	catch(...)
	{
	}
}
