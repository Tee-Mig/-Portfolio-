#include "Form.hpp"

Form::Form(): _name(""), _isSigned(false), _signGrade(150), _signExec(150)
{
	std::cout << "Default Form constructeur" << std::endl;
}

Form::Form(const std::string name, const int signGrade, const int signExec)
	: _name(name), _isSigned(0), _signGrade(signGrade), _signExec(signExec)
{
	if (signGrade < 1 || signExec < 1)
		throw Form::GradeTooHighException();
	if (signGrade > 150 || signExec > 150)
		throw Form::GradeTooLowException();
	std::cout << "Default Form constructeur 3 parameters" << std::endl;
}

Form::~Form()
{
	std::cout << "Default Form destructor" << std::endl;
}

Form& Form::operator=(const Form& cp)
{
	this->_isSigned = cp._isSigned;
	return *this;
}

Form::Form(const Form& cp): _name(cp._name), _signGrade(cp._signGrade), _signExec(cp._signExec)
{
	this->_isSigned = cp._isSigned;
}

const std::string Form::getName()
{
	return (this->_name);
}

bool Form::getIsSigned()
{
	return (this->_isSigned);
}

int Form::getSignGrade()
{
	return (this->_signGrade);
}

int Form::getSignExec()
{
	return (this->_signExec);
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "The grade is too high (need to be > 0)\n";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "The grade is too low (need to be < 151)\n";
}

void Form::beSigned(Bureaucrat & fonct)
{
	if (this->getIsSigned())
		std::cout << this->getName() << " is already signed" << std::endl;
	else if (this->getSignGrade() < fonct.getGrade())
		throw GradeTooLowException();
	else
		this->_isSigned = true;
}

std::ostream &operator<<(std::ostream& os, Form& cp)
{
	os << "The Form's name is " << cp.getName() << " and ";
	if (cp.getIsSigned() == 1)
		os << "has been signed (1)\n";
	else
		os << "has not been signed (0)\n";
	os << "The form can be signed at least by people at grade " << cp.getSignGrade() << std::endl;
	os << "The form can be executed at least by people at grade " << cp.getSignGrade() << std::endl;

	return os;
}
