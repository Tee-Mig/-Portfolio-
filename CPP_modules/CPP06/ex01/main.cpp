#include "serial.hpp"

int main()
{
	Data data;

	data.nbr = 13;
	data.c = 'M';

	std::cout << std::endl;
	std::cout << "sortie adresse data avant = " <<  &data << std::endl;
	std::cout << "sortie valeur data avant = " <<  data.nbr << std::endl;
	std::cout << "sortie valeur data avant = " <<  data.c << std::endl;

	deserialize(serialize(&data));

	std::cout << std::endl;
	std::cout << "sortie adresse data apres = " <<  &data << std::endl;
	std::cout << "sortie valeur data apres = " <<  data.nbr << std::endl;
	std::cout << "sortie valeur data apres = " <<  data.c << std::endl;
	std::cout << std::endl;

	return 0;
}