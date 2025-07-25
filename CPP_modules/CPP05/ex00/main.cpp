#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat perso1("Miguelito", 3);
	Bureaucrat perso2("Jeanpierredito", 148);
	for (int i = 0; i < 5; i++)
	{
		try
		{
			perso1.IncrementGrade();
			std::cout << perso1 << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << e.what();
			break ;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		try
		{
			perso2.DecrementGrade();
			std::cout << perso2 << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << e.what();
			break ;
		}
	}
	try
	{
		Bureaucrat perso3("JPP", 155);
	}
	catch (std::exception & e)
	{
		std::cout << "Mauvaise initialisation catch" << std::endl;
		std::cout << e.what();
	}
	return 0;
}