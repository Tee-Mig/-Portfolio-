#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <iostream>
#include <stdint.h>

typedef struct Data
{
	int			nbr;
	char		c;
}Data;

uintptr_t serialize(Data* ptr);
Data* deserialize(uintptr_t raw);

#endif