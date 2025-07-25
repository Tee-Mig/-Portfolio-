#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(): Form("PresidentialPardonForm", 25, 5), _target("")
{
	std::cout << "PresidentialPardonForm default constructor" << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "PresidentialPardonForm default destructor" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target): Form("PresidentialPardonForm", 25, 5), _target(target)
{
	std::cout << "PresidentialPardonForm default constructor with target" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &cp): Form("PresidentialPardonForm", 25, 5), _target(cp._target)
{
	std::cout << "PresidentialPardonForm copy constructor" << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &cp)
{
	(void)cp;
	std::cout << "PresidentialPardonForm operator =" << std::endl;
	return *this;
}


void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	if (this->getIsSigned() && executor.getGrade() <= this->getSignExec())
	{
		std::cout << this->_target << " has been forgiven by Zaphod Beeblebrox" << std::endl;
	}
	else if (!this->getIsSigned())
		std::cout << executor.getName() << " can't execute " << this->_target << " because " << this->_target << " is not signed" << std::endl;
	else if (executor.getGrade() > this->getSignExec())
		std::cout << executor.getName() << " can't execute " << this->_target << " because " << executor.getName() << "'s grade is not enough" << std::endl;
}
