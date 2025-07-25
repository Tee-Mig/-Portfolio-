#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): Form("RobotomyRequestForm", 72, 45), _target("")
{
	std::cout << "RobotomyRequestForm default constructor" << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "RobotomyRequestForm default destructor" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string target): Form("RobotomyRequestForm", 72, 45), _target(target)
{
	std::cout << "RobotomyRequestForm default constructor with target" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &cp): Form("RobotomyRequestForm", 72, 45), _target(cp._target)
{
	std::cout << "RobotomyRequestForm copy constructor" << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &cp)
{
	(void)cp;
	std::cout << "RobotomyRequestForm operator =" << std::endl;
	return *this;
}


void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	int robotomized;
	srand (time(NULL));
	if (this->getIsSigned() && executor.getGrade() <= this->getSignExec())
	{
		
		std::cout << "SPLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAF..." << std::endl;
		robotomized = rand() % 2;
		if (robotomized == 0)
			std::cout << this->_target << " has been robotomized" << std::endl;
		else
			std::cout << "The operation has failed :c" << std::endl;
	}
	else if (!this->getIsSigned())
		std::cout << executor.getName() << " can't execute " << this->_target << " because " << this->_target << " is not signed" << std::endl;
	else if (executor.getGrade() > this->getSignExec())
		std::cout << executor.getName() << " can't execute " << this->_target << " because " << executor.getName() << "'s grade is not enough" << std::endl;
}
