#include "easyfind.hpp"

int main()
{
	try
	{
		std::cout << std::endl << "------------------------------ Vector ------------------------------" << std::endl;
		int i = 0;
		std::vector<int> vec(10);

		std::vector<int>::iterator it;
		std::vector<int>::iterator end_it = vec.end();

		for (it = vec.begin(); it != end_it; it++)
			*it = i++;

		for (it = vec.begin(); it != end_it; it++)
			std::cout << *it << std::endl;

		std::cout << "sortie fin = " << *easyfind(vec, 5) << std::endl;
		std::cout << "sortie fin = " << *easyfind(vec, 15) << std::endl;
		
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		std::cout << std::endl << "------------------------------ List ------------------------------" << std::endl;
		int i = 0;
		std::list<int> lst(10);

		std::list<int>::iterator it;
		std::list<int>::iterator end_it = lst.end();

		for (it = lst.begin(); it != end_it; it++)
			*it = i++;

		for (it = lst.begin(); it != end_it; it++)
			std::cout << *it << std::endl;

		std::cout << "sortie fin = " << *easyfind(lst, 5) << std::endl;
		std::cout << "sortie fin = " << *easyfind(lst, 15) << std::endl;
		
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}