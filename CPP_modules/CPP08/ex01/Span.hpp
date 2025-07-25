#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <algorithm>
#include <vector>

class Span
{
	private:
		std::vector<int>	_arr;
		unsigned int		_max_len;
	public:
		Span();
		Span(unsigned int len);
		~Span();
		Span(const Span& cp);
		Span& operator=(const Span& cp);

		void addNumber(int nb);
		void addNumber(std::vector<int>& init_arr);
		void addNumber(int nb, unsigned int size);
		unsigned int shortestSpan();
		unsigned int longestSpan();
		std::vector<int> getVector();
		unsigned int getLen();
		class ArrayIsFull : public std::exception
		{
			const char *what() const throw();
		};
		class NotEnoughNumber: public std::exception
		{
			const char* what() const throw();
		};
};

std::ostream& operator<<( std::ostream& os, Span& cp);

#endif