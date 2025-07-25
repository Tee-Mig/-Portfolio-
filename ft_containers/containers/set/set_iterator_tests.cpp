#include "set.hpp"
#include <vector>
#include <map>
#include <set>

int main()
{
	std::cout << " ---------------------------- Iterator ---------------------------- " << std::endl;

	ft::set<std::string> ft_set;
	std::set<std::string> std_set;
	ft::set<std::string>::iterator ft_it;
	std::set<std::string>::iterator std_it;
	ft::set<std::string>::iterator ft_it2;
	std::set<std::string>::iterator std_it2(std_it);
	ft_it2 = ft_it;
	std_it2 = std_it;
	(void)ft_set;
	(void)std_set;
	(void)ft_it;
	(void)std_it;


	std::cout << "operator == : " << std::endl;
	// ft
	if (ft_it == ft_it2)
		std::cout << "FT: C PAREIL MEC\n";
	else
		std::cout << "FT: PAAAAAAAAAAAS PAREIL MEC\n";
	// std
	if (std_it == std_it2)
		std::cout << "STD: C PAREIL MEC\n\n";
	else
		std::cout << "STD: PAAAAAAAAAAAS PAREIL MEC\n\n";
	
	// ft
	ft_set.insert(std::string("Miguelito"));
	ft_it2 = ft_set.begin();
	if (ft_it == ft_it2)
		std::cout << "FT: C PAREIL MEC\n\n";
	else
		std::cout << "FT: PAAAAAAAAAAAS PAREIL MEC\n\n";
	// std
	std_set.insert(std::string("Miguelito"));
	std_it2 = std_set.begin();
	if (std_it == std_it2)
		std::cout << "STD: C PAREIL MEC\n\n";
	else
		std::cout << "STD: PAAAAAAAAAAAS PAREIL MEC\n\n";

	ft_set.insert(std::string("Miguel"));
	ft_set.insert(std::string("Raph"));
	ft_set.insert(std::string("Tim"));

	std_set.insert(std::string("Miguel"));
	std_set.insert(std::string("Raph"));
	std_set.insert(std::string("Tim"));

	ft_it = ft_set.begin();
	std_it = std_set.begin();
	ft_it2 = ft_set.end();
	std_it2 = std_set.end();

	ft::set<std::string>::iterator ft_end_test = ft_it2;
	ft_end_test++;
	for (int i = 0; i < 3; i++)
	{
		ft_end_test++;
		ft_end_test++;
		std::cout << "test end ft = " << *ft_end_test << std::endl;
	}

	std::cout << std::endl;

	std::set<std::string>::iterator std_end_test = std_it2;
	std_end_test++;
	for (int i = 0; i < 3; i++)
	{
		std_end_test++;
		std_end_test++;
		std::cout << "test end std = " << *std_end_test << std::endl;
	}

	std::cout << std::endl;

	ft::set<std::string>::iterator ft_begin_test = ft_it;
	ft_begin_test--;
	for (int i = 0; i < 3; i++)
	{
		ft_begin_test--;
		ft_begin_test--;
		std::cout << "test begin ft = " << *ft_begin_test << std::endl;
	}

	std::cout << std::endl;

	std::set<std::string>::iterator std_begin_test = std_it;
	std_begin_test--;
	for (int i = 0; i < 3; i++)
	{
		std_begin_test--;
		std_begin_test--;
		std::cout << "test begin std = " << *std_begin_test << std::endl;
	}

	std::cout << "!= : " << std::endl;
	if (ft_it != ft_it2)
		std::cout << "FT: C PAS PAREIL MEC\n";
	if (std_it != std_it2)
		std::cout << "STD: C PAS PAREIL MEC\n\n";

	std::cout << "ft: begin = " << *ft_it << std::endl;
	std::cout << "ft: end = " << *(--ft_it2) << std::endl << std::endl;

	for (ft::set<std::string>::iterator it = ft_it; it != ft_set.end(); it++)
		std::cout << "ft: value = " << *it << std::endl;
	std::cout << std::endl;

	std::cout << "std: begin = " << *std_it << std::endl;
	std::cout << "std: end = " << *(--std_it2) << std::endl << std::endl;

	for (std::set<std::string>::iterator it = std_it; it != std_set.end(); it++)
		std::cout << "std: value = " << *it << std::endl;
	std::cout << std::endl;

	std::cout << "ft: a->m: " << *ft_it << std::endl;
	std::cout << "std: a->m: " << *std_it << std::endl << std::endl;

	ft::set<std::string>::iterator *ft_it3 = &ft_it;
	std::set<std::string>::iterator *std_it3 = &std_it;

	std::cout << "ft: a: " << (ft_it3) << std::endl;
	std::cout << "std: a: " << (std_it3) << std::endl << std::endl;

	std::cout << "ft: a++: " << *(ft_it++) << std::endl;
	std::cout << "std: a++: " << *(std_it++) << std::endl << std::endl;

	std::cout << "ft: ++a: " << *(++ft_it) << std::endl;
	std::cout << "std: ++a: " << *(++std_it) << std::endl << std::endl;

	std::cout << "ft: a--: " << *(ft_it--) << std::endl;
	std::cout << "std: a--: " << *(std_it--) << std::endl << std::endl;

	std::cout << "ft: --a: " << *(--ft_it) << std::endl;
	std::cout << "std: --a: " << *(--std_it) << std::endl << std::endl;

	std::cout << " ---------------------------- Const iterator ---------------------------- " << std::endl;

	ft::set<std::string> ft_set_const;
	std::set<std::string> std_set_const;
	ft::set<std::string>::const_iterator ft_it_const;
	std::set<std::string>::const_iterator std_it_const;
	ft::set<std::string>::const_iterator ft_it_const2;
	std::set<std::string>::const_iterator std_it_const2;
	(void)ft_set_const;
	(void)std_set_const;
	(void)ft_it_const;
	(void)std_it_const;

	std::cout << "== : " << std::endl;
	if (ft_it_const == ft_it_const)
		std::cout << "FT: C PAREIL MEC\n";
	if (std_it_const == std_it_const)
		std::cout << "STD: C PAREIL MEC\n\n";

	ft_set_const.insert(std::string("Miguel"));
	ft_set_const.insert(std::string("Jean"));
	ft_set_const.insert(std::string("Pierre"));

	std_set_const.insert(std::string("Miguel"));
	std_set_const.insert(std::string("Jean"));
	std_set_const.insert(std::string("Pierre"));

	ft_it_const = ft_set_const.begin();
	ft_it_const2 = ft_set_const.end();
	std_it_const = std_set_const.begin();
	std_it_const2 = std_set_const.end();
	(void)std_it_const;
	(void)std_it_const2;

	ft::set<std::string>::const_iterator ft_end_const_test = ft_it_const2;
	ft_end_const_test++;
	for (int i = 0; i < 3; i++)
	{
		ft_end_const_test++;
		ft_end_const_test++;
		std::cout << "test end ft = " << *ft_end_const_test << std::endl;
	}

	std::cout << std::endl;

	std::set<std::string>::const_iterator std_end_const_test = std_it_const2;
	std_end_const_test++;
	for (int i = 0; i < 3; i++)
	{
		std_end_const_test++;
		std_end_const_test++;
		std::cout << "test end std = " << *std_end_const_test << std::endl;
	}

	std::cout << std::endl;

	if (ft_it_const != ft_it_const2)
		std::cout << "FT: C PAS PAREIL MEC\n";
	if (std_it_const != std_it_const2)
		std::cout << "STD: C PAS PAREIL MEC\n\n";

	std::cout << "ft: begin = " << *ft_it_const << std::endl;
	std::cout << "ft: end = " << *(--ft_it_const2) << std::endl << std::endl;

	for (ft::set<std::string>::const_iterator it = ft_it_const; it != ft_set_const.end(); it++)
		std::cout << "ft: value = " << *it << std::endl;
	std::cout << std::endl;

	std::cout << "std: begin = " << *std_it_const << std::endl;
	std::cout << "std: end = " << *(--std_it_const2) << std::endl << std::endl;

	for (std::set<std::string>::const_iterator it = std_it_const; it != std_set_const.end(); it++)
		std::cout << "std: value = " << *it << std::endl;
	std::cout << std::endl;

	std::cout << "ft: a->m: " << *ft_it_const << std::endl;
	std::cout << "std: a->m: " << *std_it_const << std::endl << std::endl;

	ft::set<std::string>::const_iterator *ft_it3_const = &ft_it_const;
	std::set<std::string>::const_iterator *std_it3_const = &std_it_const;

	std::cout << "ft: *a: " << (ft_it3_const) << std::endl;
	std::cout << "std: *a: " << (std_it3_const) << std::endl << std::endl;

	std::cout << "ft: a++: " << *(ft_it_const++) << std::endl;
	std::cout << "std: a++: " << *(std_it_const++) << std::endl << std::endl;

	std::cout << "ft: ++a: " << *(++ft_it_const) << std::endl;
	std::cout << "std: ++a: " << *(++std_it_const) << std::endl << std::endl;

	std::cout << "ft: a--: " << *(ft_it_const--) << std::endl;
	std::cout << "std: a--: " << *(std_it_const--) << std::endl << std::endl;

	std::cout << "ft: --a: " << *(--ft_it_const) << std::endl;
	std::cout << "std: --a: " << *(--std_it_const) << std::endl << std::endl;

	std::cout << " ---------------------------- Operators between iterator and const_iterator ---------------------------- " << std::endl;

	if (ft_it == ft_it_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (std_it == std_it_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (ft_it != ft_it_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (std_it != std_it_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << " ---------------------------- Reverse iterator ---------------------------- " << std::endl;

	ft::set<std::string> ft_set_reverse;
	std::set<std::string> std_set_reverse;
	ft::set<std::string>::reverse_iterator ft_it_reverse;
	std::set<std::string>::reverse_iterator std_it_reverse;
	ft::set<std::string>::reverse_iterator ft_it_reverse2;
	std::set<std::string>::reverse_iterator std_it_reverse2;
	(void)ft_set_reverse;
	(void)std_set_reverse;
	(void)ft_it_reverse;
	(void)std_it_reverse;

	std::cout << "== : " << std::endl;
	if (ft_it_reverse == ft_it_reverse)
		std::cout << "FT: C PAREIL MEC\n";
	if (std_it_reverse == std_it_reverse)
		std::cout << "STD: C PAREIL MEC\n\n";

	ft_set_reverse.insert(std::string("Miguel"));
	ft_set_reverse.insert(std::string("Jean"));
	ft_set_reverse.insert(std::string("Pierre"));

	std_set_reverse.insert(std::string("Miguel"));
	std_set_reverse.insert(std::string("Jean"));
	std_set_reverse.insert(std::string("Pierre"));

	ft_it_reverse = ft_set_reverse.rbegin();
	ft_it_reverse2 = ft_set_reverse.rend();
	std_it_reverse = std_set_reverse.rbegin();
	std_it_reverse2 = std_set_reverse.rend();

	ft::set<std::string>::reverse_iterator ft_end_reverse_test = ft_it_reverse2;
	ft_end_reverse_test++;
	for (int i = 0; i < 3; i++)
	{
		ft_end_reverse_test++;
		ft_end_reverse_test++;
		std::cout << "test end ft = " << *ft_end_reverse_test << std::endl;
	}

	std::cout << std::endl;

	std::set<std::string>::reverse_iterator std_end_reverse_test = std_it_reverse2;
	std_end_reverse_test++;
	for (int i = 0; i < 3; i++)
	{
		std_end_reverse_test++;
		std_end_reverse_test++;
		std::cout << "test end std = " << *std_end_reverse_test << std::endl;
	}

	std::cout << std::endl;

	ft::set<std::string>::reverse_iterator ft_begin_reverse_test = ft_it_reverse;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "test begin ft = " << *ft_begin_reverse_test << std::endl;
		ft_begin_reverse_test--;
	}

	std::cout << std::endl;

	std::set<std::string>::reverse_iterator std_begin_reverse_test = std_it_reverse;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "test begin std = " << *std_begin_reverse_test << std::endl;
		std_begin_reverse_test--;
	}

	std::cout << std::endl;

	if (ft_it_reverse != ft_it_reverse2)
		std::cout << "FT: C PAS PAREIL MEC\n";
	if (std_it_reverse != std_it_reverse2)
		std::cout << "STD: C PAS PAREIL MEC\n\n";

	std::cout << "ft: begin = " << *ft_it_reverse << std::endl;
	std::cout << "ft: end = " << *(--ft_it_reverse2) << std::endl << std::endl;

	for (ft::set<std::string>::reverse_iterator it = ft_it_reverse; it != ft_set_reverse.rend(); it++)
		std::cout << "ft: value = " << *it << std::endl;
	std::cout << std::endl;

	std::cout << "std: begin = " << *std_it_reverse << std::endl;
	std::cout << "std: end = " << *(--std_it_reverse2) << std::endl << std::endl;

	for (std::set<std::string>::reverse_iterator it = std_it_reverse; it != std_set_reverse.rend(); it++)
		std::cout << "std: value = " << *it << std::endl;
	std::cout << std::endl;

	std::cout << "ft: a->m: " << *ft_it_reverse << std::endl;
	std::cout << "std: a->m: " << *std_it_reverse << std::endl << std::endl;

	ft::set<std::string>::reverse_iterator *ft_it3_reverse = &ft_it_reverse;
	std::set<std::string>::reverse_iterator *std_it3_reverse = &std_it_reverse;

	std::cout << "ft: *a: " << (ft_it3_reverse) << std::endl;
	std::cout << "std: *a: " << (std_it3_reverse) << std::endl << std::endl;

	std::cout << "ft: a++: " << *(ft_it_reverse++) << std::endl;
	std::cout << "std: a++: " << *(std_it_reverse++) << std::endl << std::endl;

	std::cout << "ft: ++a: " << *(++ft_it_reverse) << std::endl;
	std::cout << "std: ++a: " << *(++std_it_reverse) << std::endl << std::endl;

	std::cout << "ft: a--: " << *(ft_it_reverse--) << std::endl;
	std::cout << "std: a--: " << *(std_it_reverse--) << std::endl << std::endl;

	std::cout << "ft: --a: " << *(--ft_it_reverse) << std::endl;
	std::cout << "std: --a: " << *(--std_it_reverse) << std::endl << std::endl;

	std::cout << " ---------------------------- Const reverse iterator ---------------------------- " << std::endl;

	ft::set<std::string> ft_set_reverse_const;
	std::set<std::string> std_set_reverse_const;
	ft::set<std::string>::const_reverse_iterator ft_it_reverse_const;
	std::set<std::string>::const_reverse_iterator std_it_reverse_const;
	ft::set<std::string>::const_reverse_iterator ft_it_reverse2_const;
	std::set<std::string>::const_reverse_iterator std_it_reverse2_const;
	(void)ft_set_reverse_const;
	(void)std_set_reverse_const;
	(void)ft_it_reverse_const;
	(void)std_it_reverse_const;

	std::cout << "== : " << std::endl;
	if (ft_it_reverse_const == ft_it_reverse_const)
		std::cout << "FT: C PAREIL MEC\n";
	if (std_it_reverse_const == std_it_reverse_const)
		std::cout << "STD: C PAREIL MEC\n\n";

	ft_set_reverse_const.insert(std::string("Miguel"));
	ft_set_reverse_const.insert(std::string("Jean"));
	ft_set_reverse_const.insert(std::string("Pierre"));

	std_set_reverse_const.insert(std::string("Miguel"));
	std_set_reverse_const.insert(std::string("Jean"));
	std_set_reverse_const.insert(std::string("Pierre"));

	ft_it_reverse_const = ft_set_reverse_const.rbegin();
	ft_it_reverse2_const = ft_set_reverse_const.rend();
	std_it_reverse_const = std_set_reverse_const.rbegin();
	std_it_reverse2_const = std_set_reverse_const.rend();

	ft::set<std::string>::const_reverse_iterator ft_end_reverse_test_const = ft_it_reverse2_const;
	ft_end_reverse_test_const++;
	for (int i = 0; i < 3; i++)
	{
		ft_end_reverse_test_const++;
		ft_end_reverse_test_const++;
		std::cout << "test end ft = " << *ft_end_reverse_test_const << std::endl;
	}

	std::cout << std::endl;

	std::set<std::string>::const_reverse_iterator std_end_reverse_test_const = std_it_reverse2_const;
	std_end_reverse_test_const++;
	for (int i = 0; i < 3; i++)
	{
		std_end_reverse_test_const++;
		std_end_reverse_test_const++;
		std::cout << "test end std = " << *std_end_reverse_test_const << std::endl;
	}

	std::cout << std::endl;

	ft::set<std::string>::const_reverse_iterator ft_begin_reverse_test_const = ft_it_reverse_const;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "test begin ft = " << *ft_begin_reverse_test_const << std::endl;
		ft_begin_reverse_test_const--;
	}

	std::cout << std::endl;

	std::set<std::string>::const_reverse_iterator std_begin_reverse_test_const = std_it_reverse_const;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "test begin std = " << *std_begin_reverse_test_const << std::endl;
		std_begin_reverse_test_const--;
	}

	std::cout << std::endl;

	if (ft_it_reverse_const != ft_it_reverse2_const)
		std::cout << "FT: C PAS PAREIL MEC\n";
	if (std_it_reverse_const != std_it_reverse2_const)
		std::cout << "STD: C PAS PAREIL MEC\n\n";

	std::cout << "ft: begin = " << *ft_it_reverse_const << std::endl;
	std::cout << "ft: end = " << *(--ft_it_reverse2_const) << std::endl << std::endl;

	for (ft::set<std::string>::const_reverse_iterator it = ft_it_reverse_const; it != ft_set_reverse_const.rend(); it++)
		std::cout << "ft: value = " << *it << std::endl;
	std::cout << std::endl;

	std::cout << "std: begin = " << *std_it_reverse_const << std::endl;
	std::cout << "std: end = " << *(--std_it_reverse2_const) << std::endl << std::endl;

	for (std::set<std::string>::const_reverse_iterator it = std_it_reverse_const; it != std_set_reverse_const.rend(); it++)
		std::cout << "std: value = " << *it << std::endl;
	std::cout << std::endl;

	std::cout << "ft: a->m: " << *ft_it_reverse_const << std::endl;
	std::cout << "std: a->m: " << *std_it_reverse_const << std::endl << std::endl;

	ft::set<std::string>::const_reverse_iterator *ft_it3_reverse_const = &ft_it_reverse_const;
	std::set<std::string>::const_reverse_iterator *std_it3_reverse_const = &std_it_reverse_const;

	std::cout << "ft: *a: " << (ft_it3_reverse_const) << std::endl;
	std::cout << "std: *a: " << (std_it3_reverse_const) << std::endl << std::endl;

	std::cout << "ft: a++: " << *(ft_it_reverse_const++) << std::endl;
	std::cout << "std: a++: " << *(std_it_reverse_const++) << std::endl << std::endl;

	std::cout << "ft: ++a: " << *(++ft_it_reverse_const) << std::endl;
	std::cout << "std: ++a: " << *(++std_it_reverse_const) << std::endl << std::endl;

	std::cout << "ft: a--: " << *(ft_it_reverse_const--) << std::endl;
	std::cout << "std: a--: " << *(std_it_reverse_const--) << std::endl << std::endl;

	std::cout << "ft: --a: " << *(--ft_it_reverse_const) << std::endl;
	std::cout << "std: --a: " << *(--std_it_reverse_const) << std::endl << std::endl;

	std::cout << " ---------------------------- Operators between reverse_iterator and const_reverse_iterator ---------------------------- " << std::endl;

	if (ft_it_reverse == ft_it_reverse_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (std_it_reverse == std_it_reverse_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (ft_it_reverse != ft_it_reverse_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (std_it_reverse != std_it_reverse_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	return 0;
}