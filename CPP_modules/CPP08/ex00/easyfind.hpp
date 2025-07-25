#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>

class NumberNotFound: public std::exception
{
	const char* what() const throw()
	{
		return "number not found";
	}
};

template<typename T>
typename T::iterator easyfind(T& x, int y)
{
	typename T::iterator it = std::find(x.begin(), x.end(), y);
	if (it != x.end())
		return it;
	throw NumberNotFound();
}

#endif