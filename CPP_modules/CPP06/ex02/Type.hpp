#ifndef TYPE_HPP
#define TYPE_HPP

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>

Base * generate(void);
void identify(Base* p);
void identify(Base& p);

#endif