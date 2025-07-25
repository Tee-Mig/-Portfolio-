#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include "Form.hpp"

class Form;

class Bureaucrat
{
	private:
		const std::string _name;
		int _grade;
	public:
		Bureaucrat();
		Bureaucrat(const std::string name, int grade);
		~Bureaucrat();
		Bureaucrat& operator=(const Bureaucrat& cp);
		Bureaucrat(const Bureaucrat& cp);
		const std::string getName();
		int getGrade();
		void setGrade(int grade);
		void IncrementGrade();
		void DecrementGrade();
		class GradeTooHighException: public std::exception
		{
			public:
				const char *what() const throw();
		};
		class GradeTooLowException: public std::exception
		{
			public:
				const char *what() const throw();
		};
		void signForm(Form & formulaire);
};

std::ostream & operator<<(std::ostream &os, Bureaucrat &cp);

#endif