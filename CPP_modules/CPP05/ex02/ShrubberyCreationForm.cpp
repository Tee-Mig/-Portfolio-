#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm():Form("ShrubberyCreationForm", 145, 137), _target("")
{
	std::cout << "ShrubberyCreationForm default constructor" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target): Form("ShrubberyCreationForm", 145, 137), _target(target)
{
	std::cout << "ShrubberyCreationForm target constructor with target" << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm default destructor" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &cp): Form("ShrubberyCreationForm", 145, 137), _target(cp._target)
{
	std::cout << "ShrubberyCreationForm copy constructor" << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm &cp)
{
	std::cout << "ShrubberyCreationForm operator =" << std::endl;
	(void)cp;
	return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (this->getIsSigned() && executor.getGrade() <= this->getSignExec())
	{
		std::cout << executor.getName() << " executed " << this->_target << std::endl;

		std::ofstream outfile (((std::string)this->_target + "_shrubbery").c_str());

		outfile << "           \\/ |    |/" << std::endl;
		outfile << "        \\/ / \\||/  /_/___/_" << std::endl;
		outfile << "         \\/   |/ \\/" << std::endl;
		outfile << "    _\\__\\_\\   |  /_____/_" << std::endl;
		outfile << "           \\  | /          /" << std::endl;
		outfile << "  __ _-----`  |{,-----------~" << std::endl;
		outfile << "            \\ }{" << std::endl;
		outfile << "             }{{" << std::endl;
		outfile << "             }}{" << std::endl;
		outfile << "             {{}" << std::endl;
		outfile << "       , -=-~{ .-^- _" << std::endl;
		outfile << "             `}" << std::endl;
		outfile << "              {" << std::endl;
		outfile.close();
	}
	else if (!this->getIsSigned())
		std::cout << executor.getName() << " can't execute " << this->_target << " because " << this->_target << " is not signed" << std::endl;
	else if (executor.getGrade() > this->getSignExec())
		std::cout << executor.getName() << " can't execute " << this->_target << " because " << executor.getName() << "'s grade is not enough" << std::endl;
}
