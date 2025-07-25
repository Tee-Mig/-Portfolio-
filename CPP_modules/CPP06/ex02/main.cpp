#include "Type.hpp"

int main()
{
	Base *test = generate();

	identify(test);
	identify(*test);

	return 0;
}