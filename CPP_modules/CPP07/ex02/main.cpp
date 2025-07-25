#include "Array.hpp"

int main()
{
	try
	{
		Array<unsigned int> mig(10);
		Array<unsigned int> mig3 = mig;

		std::cout << "----------- Test recopie -----------" << std::endl;
		std::cout << "mig3 = " << mig3 << std::endl;

		mig3[4] = 999;

		std::cout << "mig = " << mig << std::endl;
		std::cout << "mig3 = " << mig3 << std::endl;

		std::cout << "----------- Test recopie -----------" << std::endl << std::endl;

		std::cout << "----------- Test operateur = -----------" << std::endl;

		Array<unsigned int> mig2(1);

		std::cout << "mig2 = " << mig2 << std::endl;

		mig2 = mig;

		mig2[7] = 777;

		std::cout << "mig = " << mig << std::endl;
		std::cout << "mig2 = " << mig2 << std::endl;

		std::cout << "----------- Test operateur = -----------" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}

	return 0;
}