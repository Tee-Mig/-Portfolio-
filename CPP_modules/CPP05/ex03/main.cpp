#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
	try
	{
		// 137	-> for ShrubberyCreationForm to sign and execute
		// 45	-> for RobotomyRequestForm to sign and execute
		// 5	-> for PresidentialPardonForm to sign and execute

		Intern someRandomIntern;
		Form* rrf;
		rrf = someRandomIntern.makeForm("presidential pardon", "Bender");
		std::cout << "----------------------------------------" << std::endl;
		std::cout << *rrf << std::endl;

		Bureaucrat perso1("miguel", 5);

		std::cout << *rrf;
		std::cout << std::endl;
		perso1.signForm(*rrf);
		std::cout << std::endl;
		std::cout << *rrf;
		std::cout << std::endl;
		perso1.executeForm(*rrf);
		std::cout << std::endl;
	}
	catch(std::exception & e)
	{
		std::cout << "Error: " << e.what();
	}
	return 0;
}