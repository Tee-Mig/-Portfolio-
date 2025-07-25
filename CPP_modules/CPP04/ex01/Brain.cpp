#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Default Brain constructor" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = "Miguelito";
}

Brain::~Brain()
{
	std::cout << "Default Brain destructor" << std::endl;
}

Brain::Brain(Brain &cp)
{
	std::cout << "Brain copy assignment" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = cp.getIdeas()[i];
}

Brain &Brain::operator=(const Brain &cp)
{
	std::cout << "Brain operator =" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = cp.ideas[i];
	return (*this);
}

std::string *Brain::getIdeas()
{
	return (this->ideas);
}

void Brain::setIdeas(int id, std::string idea)
{
	if (id >= 0 && id < 100)
		this->ideas[id] = idea;
	else
		std::cout << "Error: index (must be between 0 and 99)" << std::endl;
}

void Brain::showIdeas()
{
	int nb_idea = 0;

	for (int i = 0; i < 100; i++)
	{
		if (!this->ideas[i].empty())
		{
			nb_idea++;
			std::cout << ideas[i] << std::endl;
		}
	}
	std::cout << "There is " << nb_idea << " idea(s)" << std::endl;
}