#include "iter.hpp"

void ft_apply_int(int& cell)
{
	cell += 100;
}

void ft_apply_string(const std::string& cell)
{
	std::cout << "apply string: " << cell << std::endl;
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	for(int i = 0; i < 9; i++)
		std::cout << "tab[" << i << "] = " << arr[i] << std::endl;

	iter(arr, 9, ft_apply_int);

	std::cout << "--------------------------------------" << std::endl;

	for(int i = 0; i < 9; i++)
		std::cout << "tab[" << i << "] = " << arr[i] << std::endl;

	std::cout << "--------------------------------------" << std::endl;

	const std::string arr2[] = {"Bernard", "Jean pierre", "Gerard"};
	for(int i = 0; i < 3; i++)
		std::cout << "tab[" << i << "] = " << arr2[i] << std::endl;
	
	iter(arr2, 3, ft_apply_string);

	std::cout << "--------------------------------------" << std::endl;

	for(int i = 0; i < 3; i++)
		std::cout << "tab[" << i << "] = " << arr2[i] << std::endl;

	return 0;
}
