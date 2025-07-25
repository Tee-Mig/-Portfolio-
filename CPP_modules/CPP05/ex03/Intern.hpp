#ifndef INTERN_HPP
#define INTERN_HPP

#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern
{
	public:
		Intern();
		~Intern();
		Intern(const Intern &cp);
		Intern &operator=(const Intern &cp);

		Form *makeRobotomyRequest(std::string target);
		Form *makePresidentialPardon(std::string target);
		Form *makeShrubberyCreation(std::string target);

		Form *makeForm(std::string form, std::string target);

		class FormNotFound: public std::exception
		{
			public:
				const char*what() const throw();
		};
};

#endif