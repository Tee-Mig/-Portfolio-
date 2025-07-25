#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try
	{
		Form form1("fomulaire1", 8, 120);
		Bureaucrat perso1("Miguel", 8);
		std::cout << form1 << std::endl;
		perso1.signForm(form1);
		std::cout << std::endl;
		perso1.signForm(form1);
		std::cout << std::endl;
		std::cout << form1 << std::endl;
	}
	catch(std::exception & e)
	{
		std::cout << "Error: " << e.what();
	}
	return 0;
}