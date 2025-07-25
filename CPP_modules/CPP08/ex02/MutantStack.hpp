#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <stack>
#include <deque>
#include <algorithm>

template<typename T>
class MutantStack: public std::stack<T>
{
	public:
		MutantStack() {};
		MutantStack(const MutantStack<T>& cp)
		{
			*this = cp;
		};
		MutantStack<T>& operator=(const MutantStack<T>& cp)
		{
			this->c = cp.c;
			return *this;
		};
		~MutantStack() {};

		typedef typename std::deque<T>::iterator iterator;

		iterator begin()
		{
			return this->c.begin();
		};

		iterator end()
		{
			return this->c.end();
		};
};

template<typename T>
std::ostream& operator<<( std::ostream& os, MutantStack<T>& cp)
{
	typename MutantStack<T>::iterator it;

	for (it = cp.begin(); it != cp.end(); it++)
		os << *it << std::endl;
	return os;
}

#endif