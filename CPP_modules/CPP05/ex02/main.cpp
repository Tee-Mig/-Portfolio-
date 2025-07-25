#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	try
	{
		// ShrubberyCreationForm form1("form1");
		// std::cout << std::endl;
		// Bureaucrat perso1("miguel", 137);
		// std::cout << std::endl;
		// std::cout << form1;
		// std::cout << std::endl;
		// perso1.signForm(form1);
		// std::cout << std::endl;
		// std::cout << form1;
		// std::cout << std::endl;
		// perso1.executeForm(form1);
		// std::cout << std::endl;

		// RobotomyRequestForm form1("form1");
		// std::cout << std::endl;
		// Bureaucrat perso1("miguel", 45);
		// std::cout << std::endl;
		// std::cout << form1;
		// std::cout << std::endl;
		// perso1.signForm(form1);
		// std::cout << std::endl;
		// std::cout << form1;
		// std::cout << std::endl;
		// perso1.executeForm(form1);
		// std::cout << std::endl;

		PresidentialPardonForm form1("form1");
		std::cout << std::endl;
		Bureaucrat perso1("miguel", 5);
		std::cout << std::endl;
		std::cout << form1;
		std::cout << std::endl;
		perso1.signForm(form1);
		std::cout << std::endl;
		std::cout << form1;
		std::cout << std::endl;
		perso1.executeForm(form1);
		std::cout << std::endl;
	}
	catch(std::exception & e)
	{
		std::cout << "Error: " << e.what();
	}
	return 0;
}