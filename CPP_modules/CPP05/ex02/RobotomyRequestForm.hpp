#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "Form.hpp"
#include <cstdlib>

class RobotomyRequestForm: public Form
{
	private:
		std::string _target;
	public:
		RobotomyRequestForm();
		~RobotomyRequestForm();
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(const RobotomyRequestForm &cp);
		RobotomyRequestForm &operator=(const RobotomyRequestForm &cp);

		void execute(Bureaucrat const &executor) const;
};


#endif