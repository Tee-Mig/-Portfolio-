#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template<typename T>
void iter(T *addr, int len, void(*f)(T& cell))
{
	for (int i = 0; i < len; i++)
	{
		f(addr[i]);
	}
}

template<typename T>
void iter(T const *addr, int len, void(*f)(T const& cell))
{
	for (int i = 0; i < len; i++)
	{
		f(addr[i]);
	}
}

#endif