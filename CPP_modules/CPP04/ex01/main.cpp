#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"

const char SIZE_ARRAY = 10;

int main()
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "\n";

	//Deep Copy
	Dog doggo1;
	Cat doggo2;

	std::cout << "\n";

	Dog & doggo1_ref = doggo1;
	Cat & doggo2_ref = doggo2;

	Dog doggo1_cp(doggo1_ref);
	Cat doggo2_cp(doggo2_ref);

	std::cout << "\n";
	
	(void)doggo1_ref;
	(void)doggo2_ref;

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
