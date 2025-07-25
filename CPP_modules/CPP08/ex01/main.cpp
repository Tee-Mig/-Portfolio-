#include "Span.hpp"

int main()
{
	try
	{
		Span mig(100000);

		int arr_init[] = {93223434, 234, 234342, 13213123};
		int n = sizeof(arr_init) / sizeof(arr_init[0]);

		std::vector<int> arr(arr_init, arr_init + n);

		mig.addNumber(arr);

		mig.addNumber(13, 99994);

		mig.addNumber(932234345);
		mig.addNumber(2341);

		// std::cout << mig << std::endl;

		std::cout << "Shortest span = " << mig.shortestSpan() << std::endl;
		std::cout << "Longest span = " << mig.longestSpan() << std::endl;

	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}