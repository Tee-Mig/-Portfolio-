#include "Span.hpp"

void Span::addNumber(int nb)
{
	if (this->_max_len > this->_arr.size())
	{
		this->_arr.push_back(nb);
		return ;
	}
	throw ArrayIsFull();
}

void Span::addNumber(std::vector<int>& init_arr)
{
	if (this->_max_len >= init_arr.size())
	{
		this->_arr.insert(this->_arr.end(), init_arr.begin(), init_arr.end());
		return ;
	}
	throw ArrayIsFull();
}

void Span::addNumber(int nb, unsigned int size)
{
	if (this->_max_len >= this->_arr.size() + size)
	{
		for (unsigned int i = 0; i < size; i++)
			this->_arr.push_back(nb);
		return ;
	}
	throw ArrayIsFull();
}

Span::Span(const Span& cp)
{
	this->_max_len = cp._max_len;
	this->_arr = cp._arr;
	std::cout << "copy constructor" << std::endl;
}

Span& Span::operator=(const Span& cp)
{
	std::cout << "operator = " << std::endl;
	this->_max_len = cp._max_len;
	this->_arr = cp._arr;
	return *this;
}


unsigned int Span::shortestSpan()
{
	std::vector<int>	arr_tmp = this->_arr;
	unsigned int shortSpan = 4294967295;

	if (this->_arr.size() < 2)
		throw NotEnoughNumber();

	std::sort(arr_tmp.begin(), arr_tmp.end());
	for (unsigned long int i = 0; i < arr_tmp.size() - 1; i++)
	{
		if (static_cast<unsigned int>(arr_tmp[i + 1] - arr_tmp[i]) < shortSpan)
			shortSpan = (arr_tmp[i + 1] - arr_tmp[i]);
	}
	return shortSpan;
}

unsigned int Span::longestSpan()
{
	if (this->_arr.size() < 2)
		throw NotEnoughNumber();
	int maxVal = *std::max_element(this->_arr.begin(), this->_arr.end());
	int minVal = *std::min_element(this->_arr.begin(), this->_arr.end());

	return (maxVal - minVal);
}

Span::Span(): _max_len(0)
{
	std::cout << "Default Span constructor " << std::endl;
}

Span::Span(unsigned int len): _max_len(len) {}

Span::~Span()
{
	std::cout << "Default Span destructor " << std::endl;
}


const char* Span::ArrayIsFull::what() const throw()
{
	return "array is full";
}

const char* Span::NotEnoughNumber::what() const throw()
{
	return "not enough number in array";
}

unsigned int Span::getLen()
{
	return this->_max_len;
}

std::vector<int> Span::getVector()
{
	return this->_arr;
}

std::ostream& operator<<( std::ostream& os, Span& cp)
{
	for (unsigned int i = 0; i < cp.getLen(); i++)
		os << cp.getVector()[i] << std::endl;
	return os;
}
