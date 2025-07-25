#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	const WrongAnimal* meta = new WrongAnimal();
	const WrongAnimal* meta2 = new WrongCat();
	const Animal* j = new Dog();
	const Animal* k = new Animal();
	const Animal* m = new Cat();
	const WrongCat* i = new WrongCat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	std::cout << meta->getType() << " " << std::endl;
	std::cout << meta2->getType() << " " << std::endl;
	std::cout << k->getType() << " " << std::endl;

	i->makeSound(); //will output the cat sound!
	j->makeSound();
	k->makeSound();
	m->makeSound();
	meta->makeSound();
	meta2->makeSound();

	delete meta;
	delete meta2;
	delete j;
	delete i;
	delete k;
	delete m;
	return 0;
}
