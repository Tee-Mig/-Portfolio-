#include "Intern.hpp"

Intern::Intern()
{
	std::cout << "Default Intern constructor" << std::endl;
}

Intern::~Intern()
{
	std::cout << "Default Intern destructor" << std::endl;
}

Intern::Intern(const Intern &cp)
{
	(void)cp;
	std::cout << "Intern copy constructor" << std::endl;
}

Intern &Intern::operator=(const Intern &cp)
{
	(void)cp;
	std::cout << "Intern operator = " << std::endl;
	return *this;
}

const char* Intern::FormNotFound::what() const throw()
{
	return "Form doesn't exist\n";
}

Form *Intern::makeRobotomyRequest(std::string target)
{
	return new RobotomyRequestForm(target);
}

Form *Intern::makePresidentialPardon(std::string target)
{
	return new PresidentialPardonForm(target);
}

Form *Intern::makeShrubberyCreation(std::string target)
{
	return new ShrubberyCreationForm(target);
}

Form *Intern::makeForm(std::string form, std::string target)
{
	Form *(Intern::*functions[3])(std::string target) = {&Intern::makeRobotomyRequest, &Intern::makePresidentialPardon, &Intern::makeShrubberyCreation};
	std::string forms[3] = {"robotomy request", "presidential pardon", "shrubbery creation"};
	for (int i = 0; i < 3; i++)
	{
		if (forms[i] == form)
		{
			std::cout << "Intern creates " << form << std::endl;
			return (this->*functions[i])(target);
		}
	}
	throw FormNotFound();
}