#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"

const char SIZE_ARRAY = 10;

int main()
{
	//Les 2 lignes fails si on les decommente car Animal est une classe abstraite
	//const Animal test = new Animal();
	//const Animal test2;

	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "\n";

	{
		Dog * basic = new Dog();
		Animal * tmp = new Dog(*basic);

		delete basic;
		delete tmp;
	}

	std::cout << "\n";

	//fill Animal array with Cat and Dog
	Animal *animal_array[SIZE_ARRAY];
	for (int i = 0; i < SIZE_ARRAY / 2; i++)
		animal_array[i] = new Dog();
	for (int i = SIZE_ARRAY / 2; i < SIZE_ARRAY; i++)
		animal_array[i] = new Cat();
	for (int i = 0; i < SIZE_ARRAY; i++)
		std::cout << "sortie = " << animal_array[i]->getType() << "\n";

	for (int i = 0; i < SIZE_ARRAY; i++)
		delete animal_array[i];

	std::cout << "\n";

	delete j;//should not create a leak
	delete i;

	return 0;
}
