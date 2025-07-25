#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	private:
		const std::string _name;
		bool _isSigned;
		const int _signGrade;
		const int _signExec;
	public:
		Form();
		Form(const std::string name, const int signGrade, const int signExec);
		~Form();
		Form& operator=(const Form& cp);
		Form(const Form& cp);

		const std::string getName();
		bool getIsSigned();
		int getSignGrade();
		int getSignExec();

		class GradeTooHighException: public std::exception
		{
			const char *what() const throw();
		};
		class GradeTooLowException: public std::exception
		{
			const char *what() const throw();
		};

		void beSigned(Bureaucrat & fonct);
};

std::ostream &operator<<(std::ostream& os, Form& cp);

#endif