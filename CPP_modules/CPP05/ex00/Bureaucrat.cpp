#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
	std::cout << "Default Bureaucrat constructor" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string name, int grade): _name(name), _grade(grade)
{
	if (this->_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (this->_grade > 150)
		throw Bureaucrat::GradeTooLowException();
	std::cout << "Default Bureaucrat constructor with name and grade" << std::endl;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Default Bureaucrat destructor" << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& cp)
{
	std::cout << "Default Bureaucrat operator =" << std::endl;
	this->_grade = cp._grade;
	return (*this);
}

Bureaucrat::Bureaucrat(const Bureaucrat& cp): _name(cp._name)
{
	std::cout << "Default Bureaucrat copy assignment" << std::endl;
	this->_grade = cp._grade;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	 return "The grade is too high (need to be > 0)\n";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	 return "The grade is too low (need to be < 151)\n";
}

const std::string Bureaucrat::getName()
{
	return (this->_name);
}

int Bureaucrat::getGrade()
{
	return (this->_grade);
}

void Bureaucrat::setGrade(int grade)
{
	this->_grade = grade;
}

void Bureaucrat::IncrementGrade()
{
	if (this->_grade - 1 < 1)
	{
		throw Bureaucrat::GradeTooHighException();
	}
	else
		this->_grade--;
}

void Bureaucrat::DecrementGrade()
{
	if (this->_grade + 1 > 150)
	{
		throw Bureaucrat::GradeTooLowException();
	}
	else
		this->_grade++;
}

std::ostream & operator<<(std::ostream &os, Bureaucrat &cp)
{
	os << "Bureaucrat " << cp.getName() << " has grade " << cp.getGrade();
	return os;
}
