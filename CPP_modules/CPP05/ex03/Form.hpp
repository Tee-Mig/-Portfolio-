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

		const std::string getName() const;
		bool getIsSigned() const;
		int getSignGrade() const;
		int getSignExec() const;

		class GradeTooHighException: public std::exception
		{
			const char *what() const throw();
		};
		class GradeTooLowException: public std::exception
		{
			const char *what() const throw();
		};

		void beSigned(const Bureaucrat & fonct);
		virtual void execute(Bureaucrat const &executor) const = 0;
};

std::ostream &operator<<(std::ostream& os, Form& cp);

#endif