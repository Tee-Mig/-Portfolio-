#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template<typename T>
class Array 
{
	private:
		T				*_arr;
		unsigned int	_len;
	public:
		Array();
		~Array();
		Array(unsigned int n);
		Array(const Array<T>& cp);
		Array<T>& operator=(const Array<T>& cp);

		class InvalidIndex: public std::exception
		{
			public:
				const char* what() const throw();
		};
		T& operator[](unsigned int id);
		unsigned int size() const;
};

template<typename T>
Array<T>::Array(): _len(0)
{
	std::cout << "Default Array contructor" << std::endl;
	this->_arr = new T[0];
}

template<typename T>
Array<T>::~Array()
{
	std::cout << "Default Array destructor" << std::endl;
	delete[] this->_arr;
}

template<typename T>
Array<T>::Array(unsigned int n): _len(n)
{
	std::cout << "Array contructor with n" << std::endl;
	this->_arr = new T[n]();
}

template<typename T>
Array<T>::Array(const Array<T>& cp)
{
	std::cout << "Constructor de recopie" << std::endl;
	this->_arr = new T[cp.size()];
	this->_len = cp._len;
	for (unsigned int i = 0; i < cp.size(); i++)
		this->_arr[i] = cp._arr[i];
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& cp)
{
	if (this != &cp)
	{
		delete[] this->_arr;
		this->_arr = new T[cp.size()];
		this->_len = cp._len;
		for (unsigned int i = 0; i < cp.size(); i++)
			this->_arr[i] = cp._arr[i];
	}
	return *this;
}

template<typename T>
const char* Array<T>::InvalidIndex::what() const throw()
{
	return "invalid index";
}

template<typename T>
unsigned int Array<T>::size() const
{
	return this->_len;
}

template<typename T>
T& Array<T>::operator[](unsigned int id)
{
	if (id < this->_len)
		return this->_arr[id];
	else
		throw InvalidIndex();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Array<T> &cp)
{
	for (unsigned int i = 0; i < cp.size(); i++)
		os << "arr[" << i << "] = " << cp[i] << std::endl;
	return os;
}

#endif