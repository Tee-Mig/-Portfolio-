#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain
{
	private:
		std::string ideas[100];
	public:
		Brain();
		~Brain();
		Brain(Brain &cp);
		Brain &operator=(const Brain &cp);
		std::string *getIdeas();
		void setIdeas(int id, std::string idea);
		void showIdeas();
};

#endif