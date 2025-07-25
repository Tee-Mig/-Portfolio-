#include "map.hpp"
#include <vector>
#include <map>

int map_iterator_tests()
{
	std::cout << " ---------------------------- Iterator ---------------------------- " << std::endl;

	ft::map<std::string, std::string> ft_map;
	std::map<std::string, std::string> std_map;
	ft::map<std::string, std::string>::iterator ft_it;
	std::map<std::string, std::string>::iterator std_it;
	ft::map<std::string, std::string>::iterator ft_it2;
	std::map<std::string, std::string>::iterator std_it2(std_it);
	ft_it2 = ft_it;
	std_it2 = std_it;
	(void)ft_map;
	(void)std_map;
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
	ft_map["666"] = "Miguelito";
	ft_it2 = ft_map.begin();
	if (ft_it == ft_it2)
		std::cout << "FT: C PAREIL MEC\n\n";
	else
		std::cout << "FT: PAAAAAAAAAAAS PAREIL MEC\n\n";
	// std
	std_map["666"] = "Miguelito";
	std_it2 = std_map.begin();
	if (std_it == std_it2)
		std::cout << "STD: C PAREIL MEC\n\n";
	else
		std::cout << "STD: PAAAAAAAAAAAS PAREIL MEC\n\n";

	ft_map["777"] = "Miguel";
	ft_map["888"] = "Raph";
	ft_map["999"] = "Tim";

	std_map["777"] = "Miguel";
	std_map["888"] = "Raph";
	std_map["999"] = "Tim";

	ft_it = ft_map.begin();
	std_it = std_map.begin();
	ft_it2 = ft_map.end();
	std_it2 = std_map.end();

	ft::map<std::string, std::string>::iterator ft_end_test = ft_it2;
	ft_end_test++;
	for (int i = 0; i < 3; i++)
	{
		ft_end_test++;
		ft_end_test++;
		std::cout << "test end ft = " << ft_end_test->first << std::endl;
	}

	std::cout << std::endl;

	std::map<std::string, std::string>::iterator std_end_test = std_it2;
	std_end_test++;
	for (int i = 0; i < 3; i++)
	{
		std_end_test++;
		std_end_test++;
		std::cout << "test end std = " << std_end_test->first << std::endl;
	}

	std::cout << std::endl;

	ft::map<std::string, std::string>::iterator ft_begin_test = ft_it;
	ft_begin_test--;
	for (int i = 0; i < 3; i++)
	{
		ft_begin_test--;
		ft_begin_test--;
		std::cout << "test begin ft = " << ft_begin_test->first << std::endl;
	}

	std::cout << std::endl;

	std::map<std::string, std::string>::iterator std_begin_test = std_it;
	std_begin_test--;
	for (int i = 0; i < 3; i++)
	{
		std_begin_test--;
		std_begin_test--;
		std::cout << "test begin std = " << std_begin_test->first << std::endl;
	}

	std::cout << "!= : " << std::endl;
	if (ft_it != ft_it2)
		std::cout << "FT: C PAS PAREIL MEC\n";
	if (std_it != std_it2)
		std::cout << "STD: C PAS PAREIL MEC\n\n";

	std::cout << "ft: begin = " << ft_it->first << std::endl;
	std::cout << "ft: end = " << (--ft_it2)->first << std::endl << std::endl;

	for (ft::map<std::string, std::string>::iterator it = ft_it; it != ft_map.end(); it++)
		std::cout << "ft: value = " << it->first << std::endl;
	std::cout << std::endl;

	std::cout << "std: begin = " << std_it->first << std::endl;
	std::cout << "std: end = " << (--std_it2)->first << std::endl << std::endl;

	for (std::map<std::string, std::string>::iterator it = std_it; it != std_map.end(); it++)
		std::cout << "std: value = " << it->first << std::endl;
	std::cout << std::endl;

	std::cout << "ft: a->m: " << ft_it->first << std::endl;
	std::cout << "std: a->m: " << std_it->first << std::endl << std::endl;

	ft::map<std::string, std::string>::iterator *ft_it3 = &ft_it;
	std::map<std::string, std::string>::iterator *std_it3 = &std_it;

	std::cout << "ft: *a: " << (*ft_it3)->first << std::endl;
	std::cout << "std: *a: " << (*std_it3)->first << std::endl << std::endl;

	std::cout << "ft: a++: " << (ft_it++)->first << std::endl;
	std::cout << "std: a++: " << (std_it++)->first << std::endl << std::endl;

	std::cout << "ft: ++a: " << (++ft_it)->first << std::endl;
	std::cout << "std: ++a: " << (++std_it)->first << std::endl << std::endl;

	std::cout << "ft: a--: " << (ft_it--)->first << std::endl;
	std::cout << "std: a--: " << (std_it--)->first << std::endl << std::endl;

	std::cout << "ft: --a: " << (--ft_it)->first << std::endl;
	std::cout << "std: --a: " << (--std_it)->first << std::endl << std::endl;

	std::cout << " ---------------------------- Const iterator ---------------------------- " << std::endl;

	ft::map<std::string, std::string> ft_map_const;
	std::map<std::string, std::string> std_map_const;
	ft::map<std::string, std::string>::const_iterator ft_it_const;
	std::map<std::string, std::string>::const_iterator std_it_const;
	ft::map<std::string, std::string>::const_iterator ft_it_const2;
	std::map<std::string, std::string>::const_iterator std_it_const2;
	(void)ft_map_const;
	(void)std_map_const;
	(void)ft_it_const;
	(void)std_it_const;

	std::cout << "== : " << std::endl;
	if (ft_it_const == ft_it_const)
		std::cout << "FT: C PAREIL MEC\n";
	if (std_it_const == std_it_const)
		std::cout << "STD: C PAREIL MEC\n\n";

	ft_map_const["777"] = "Miguel";
	ft_map_const["888"] = "Jean";
	ft_map_const["999"] = "Pierre";

	std_map_const["777"] = "Miguel";
	std_map_const["888"] = "Jean";
	std_map_const["999"] = "Pierre";

	ft_it_const = ft_map_const.begin();
	ft_it_const2 = ft_map_const.end();
	std_it_const = std_map_const.begin();
	std_it_const2 = std_map_const.end();
	(void)std_it_const;
	(void)std_it_const2;

	ft::map<std::string, std::string>::const_iterator ft_end_const_test = ft_it_const2;
	ft_end_const_test++;
	for (int i = 0; i < 3; i++)
	{
		ft_end_const_test++;
		ft_end_const_test++;
		std::cout << "test end ft = " << ft_end_const_test->first << std::endl;
	}

	std::cout << std::endl;

	std::map<std::string, std::string>::const_iterator std_end_const_test = std_it_const2;
	std_end_const_test++;
	for (int i = 0; i < 3; i++)
	{
		std_end_const_test++;
		std_end_const_test++;
		std::cout << "test end std = " << std_end_const_test->first << std::endl;
	}

	std::cout << std::endl;

	if (ft_it_const != ft_it_const2)
		std::cout << "FT: C PAS PAREIL MEC\n";
	if (std_it_const != std_it_const2)
		std::cout << "STD: C PAS PAREIL MEC\n\n";

	std::cout << "ft: begin = " << ft_it_const->first << std::endl;
	std::cout << "ft: end = " << (--ft_it_const2)->first << std::endl << std::endl;

	for (ft::map<std::string, std::string>::const_iterator it = ft_it_const; it != ft_map_const.end(); it++)
		std::cout << "ft: value = " << it->first << std::endl;
	std::cout << std::endl;

	std::cout << "std: begin = " << std_it_const->first << std::endl;
	std::cout << "std: end = " << (--std_it_const2)->first << std::endl << std::endl;

	for (std::map<std::string, std::string>::const_iterator it = std_it_const; it != std_map_const.end(); it++)
		std::cout << "std: value = " << it->first << std::endl;
	std::cout << std::endl;

	std::cout << "ft: a->m: " << ft_it_const->first << std::endl;
	std::cout << "std: a->m: " << std_it_const->first << std::endl << std::endl;

	ft::map<std::string, std::string>::const_iterator *ft_it3_const = &ft_it_const;
	std::map<std::string, std::string>::const_iterator *std_it3_const = &std_it_const;

	std::cout << "ft: *a: " << (*ft_it3_const)->first << std::endl;
	std::cout << "std: *a: " << (*std_it3_const)->first << std::endl << std::endl;

	std::cout << "ft: a++: " << (ft_it_const++)->first << std::endl;
	std::cout << "std: a++: " << (std_it_const++)->first << std::endl << std::endl;

	std::cout << "ft: ++a: " << (++ft_it_const)->first << std::endl;
	std::cout << "std: ++a: " << (++std_it_const)->first << std::endl << std::endl;

	std::cout << "ft: a--: " << (ft_it_const--)->first << std::endl;
	std::cout << "std: a--: " << (std_it_const--)->first << std::endl << std::endl;

	std::cout << "ft: --a: " << (--ft_it_const)->first << std::endl;
	std::cout << "std: --a: " << (--std_it_const)->first << std::endl << std::endl;

	// std::cout << " ---------------------------- Operators between iterator and const_iterator ---------------------------- " << std::endl;

	// if (ft_it == ft_it_const)
	// 	std::cout << "ft: pareil\n";
	// else
	// 	std::cout << "ft: pas pareil\n";

	// if (std_it == std_it_const)
	// 	std::cout << "std: pareil\n";
	// else
	// 	std::cout << "std: pas pareil\n";

	// std::cout << std::endl;

	// if (ft_it != ft_it_const)
	// 	std::cout << "ft: pareil\n";
	// else
	// 	std::cout << "ft: pas pareil\n";

	// if (std_it != std_it_const)
	// 	std::cout << "std: pareil\n";
	// else
	// 	std::cout << "std: pas pareil\n";

	std::cout << " ---------------------------- Reverse iterator ---------------------------- " << std::endl;

	ft::map<std::string, std::string> ft_map_reverse;
	std::map<std::string, std::string> std_map_reverse;
	ft::map<std::string, std::string>::reverse_iterator ft_it_reverse;
	std::map<std::string, std::string>::reverse_iterator std_it_reverse;
	ft::map<std::string, std::string>::reverse_iterator ft_it_reverse2;
	std::map<std::string, std::string>::reverse_iterator std_it_reverse2;
	(void)ft_map_reverse;
	(void)std_map_reverse;
	(void)ft_it_reverse;
	(void)std_it_reverse;

	std::cout << "== : " << std::endl;
	if (ft_it_reverse == ft_it_reverse)
		std::cout << "FT: C PAREIL MEC\n";
	if (std_it_reverse == std_it_reverse)
		std::cout << "STD: C PAREIL MEC\n\n";

	ft_map_reverse["777"] = "Miguel";
	ft_map_reverse["888"] = "Jean";
	ft_map_reverse["999"] = "Pierre";

	std_map_reverse["777"] = "Miguel";
	std_map_reverse["888"] = "Jean";
	std_map_reverse["999"] = "Pierre";

	ft_it_reverse = ft_map_reverse.rbegin();
	ft_it_reverse2 = ft_map_reverse.rend();
	std_it_reverse = std_map_reverse.rbegin();
	std_it_reverse2 = std_map_reverse.rend();

	ft::map<std::string, std::string>::reverse_iterator ft_end_reverse_test = ft_it_reverse2;
	ft_end_reverse_test++;
	for (int i = 0; i < 3; i++)
	{
		ft_end_reverse_test++;
		ft_end_reverse_test++;
		std::cout << "test end ft = " << ft_end_reverse_test->first << std::endl;
	}

	std::cout << std::endl;

	std::map<std::string, std::string>::reverse_iterator std_end_reverse_test = std_it_reverse2;
	std_end_reverse_test++;
	for (int i = 0; i < 3; i++)
	{
		std_end_reverse_test++;
		std_end_reverse_test++;
		std::cout << "test end std = " << std_end_reverse_test->first << std::endl;
	}

	std::cout << std::endl;

	ft::map<std::string, std::string>::reverse_iterator ft_begin_reverse_test = ft_it_reverse;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "test begin ft = " << ft_begin_reverse_test->first << std::endl;
		ft_begin_reverse_test--;
	}

	std::cout << std::endl;

	std::map<std::string, std::string>::reverse_iterator std_begin_reverse_test = std_it_reverse;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "test begin std = " << std_begin_reverse_test->first << std::endl;
		std_begin_reverse_test--;
	}

	std::cout << std::endl;

	if (ft_it_reverse != ft_it_reverse2)
		std::cout << "FT: C PAS PAREIL MEC\n";
	if (std_it_reverse != std_it_reverse2)
		std::cout << "STD: C PAS PAREIL MEC\n\n";

	std::cout << "ft: begin = " << ft_it_reverse->first << std::endl;
	std::cout << "ft: end = " << (--ft_it_reverse2)->first << std::endl << std::endl;

	for (ft::map<std::string, std::string>::reverse_iterator it = ft_it_reverse; it != ft_map_reverse.rend(); it++)
		std::cout << "ft: value = " << it->first << std::endl;
	std::cout << std::endl;

	std::cout << "std: begin = " << std_it_reverse->first << std::endl;
	std::cout << "std: end = " << (--std_it_reverse2)->first << std::endl << std::endl;

	for (std::map<std::string, std::string>::reverse_iterator it = std_it_reverse; it != std_map_reverse.rend(); it++)
		std::cout << "std: value = " << it->first << std::endl;
	std::cout << std::endl;

	std::cout << "ft: a->m: " << ft_it_reverse->first << std::endl;
	std::cout << "std: a->m: " << std_it_reverse->first << std::endl << std::endl;

	ft::map<std::string, std::string>::reverse_iterator *ft_it3_reverse = &ft_it_reverse;
	std::map<std::string, std::string>::reverse_iterator *std_it3_reverse = &std_it_reverse;

	std::cout << "ft: *a: " << (*ft_it3_reverse)->first << std::endl;
	std::cout << "std: *a: " << (*std_it3_reverse)->first << std::endl << std::endl;

	std::cout << "ft: a++: " << (ft_it_reverse++)->first << std::endl;
	std::cout << "std: a++: " << (std_it_reverse++)->first << std::endl << std::endl;

	std::cout << "ft: ++a: " << (++ft_it_reverse)->first << std::endl;
	std::cout << "std: ++a: " << (++std_it_reverse)->first << std::endl << std::endl;

	std::cout << "ft: a--: " << (ft_it_reverse--)->first << std::endl;
	std::cout << "std: a--: " << (std_it_reverse--)->first << std::endl << std::endl;

	std::cout << "ft: --a: " << (--ft_it_reverse)->first << std::endl;
	std::cout << "std: --a: " << (--std_it_reverse)->first << std::endl << std::endl;

	std::cout << " ---------------------------- Const reverse iterator ---------------------------- " << std::endl;

	ft::map<std::string, std::string> ft_map_reverse_const;
	std::map<std::string, std::string> std_map_reverse_const;
	ft::map<std::string, std::string>::const_reverse_iterator ft_it_reverse_const;
	std::map<std::string, std::string>::const_reverse_iterator std_it_reverse_const;
	ft::map<std::string, std::string>::const_reverse_iterator ft_it_reverse2_const;
	std::map<std::string, std::string>::const_reverse_iterator std_it_reverse2_const;
	(void)ft_map_reverse_const;
	(void)std_map_reverse_const;
	(void)ft_it_reverse_const;
	(void)std_it_reverse_const;

	std::cout << "== : " << std::endl;
	if (ft_it_reverse_const == ft_it_reverse_const)
		std::cout << "FT: C PAREIL MEC\n";
	if (std_it_reverse_const == std_it_reverse_const)
		std::cout << "STD: C PAREIL MEC\n\n";

	ft_map_reverse_const["777"] = "Miguel";
	ft_map_reverse_const["888"] = "Jean";
	ft_map_reverse_const["999"] = "Pierre";

	std_map_reverse_const["777"] = "Miguel";
	std_map_reverse_const["888"] = "Jean";
	std_map_reverse_const["999"] = "Pierre";

	ft_it_reverse_const = ft_map_reverse_const.rbegin();
	ft_it_reverse2_const = ft_map_reverse_const.rend();
	std_it_reverse_const = std_map_reverse_const.rbegin();
	std_it_reverse2_const = std_map_reverse_const.rend();

	ft::map<std::string, std::string>::const_reverse_iterator ft_end_reverse_test_const = ft_it_reverse2_const;
	ft_end_reverse_test_const++;
	for (int i = 0; i < 3; i++)
	{
		ft_end_reverse_test_const++;
		ft_end_reverse_test_const++;
		std::cout << "test end ft = " << ft_end_reverse_test_const->first << std::endl;
	}

	std::cout << std::endl;

	std::map<std::string, std::string>::const_reverse_iterator std_end_reverse_test_const = std_it_reverse2_const;
	std_end_reverse_test_const++;
	for (int i = 0; i < 3; i++)
	{
		std_end_reverse_test_const++;
		std_end_reverse_test_const++;
		std::cout << "test end std = " << std_end_reverse_test_const->first << std::endl;
	}

	std::cout << std::endl;

	ft::map<std::string, std::string>::const_reverse_iterator ft_begin_reverse_test_const = ft_it_reverse_const;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "test begin ft = " << ft_begin_reverse_test_const->first << std::endl;
		ft_begin_reverse_test_const--;
	}

	std::cout << std::endl;

	std::map<std::string, std::string>::const_reverse_iterator std_begin_reverse_test_const = std_it_reverse_const;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "test begin std = " << std_begin_reverse_test_const->first << std::endl;
		std_begin_reverse_test_const--;
	}

	std::cout << std::endl;

	if (ft_it_reverse_const != ft_it_reverse2_const)
		std::cout << "FT: C PAS PAREIL MEC\n";
	if (std_it_reverse_const != std_it_reverse2_const)
		std::cout << "STD: C PAS PAREIL MEC\n\n";

	std::cout << "ft: begin = " << ft_it_reverse_const->first << std::endl;
	std::cout << "ft: end = " << (--ft_it_reverse2_const)->first << std::endl << std::endl;

	for (ft::map<std::string, std::string>::const_reverse_iterator it = ft_it_reverse_const; it != ft_map_reverse_const.rend(); it++)
		std::cout << "ft: value = " << it->first << std::endl;
	std::cout << std::endl;

	std::cout << "std: begin = " << std_it_reverse_const->first << std::endl;
	std::cout << "std: end = " << (--std_it_reverse2_const)->first << std::endl << std::endl;

	for (std::map<std::string, std::string>::const_reverse_iterator it = std_it_reverse_const; it != std_map_reverse_const.rend(); it++)
		std::cout << "std: value = " << it->first << std::endl;
	std::cout << std::endl;

	std::cout << "ft: a->m: " << ft_it_reverse_const->first << std::endl;
	std::cout << "std: a->m: " << std_it_reverse_const->first << std::endl << std::endl;

	ft::map<std::string, std::string>::const_reverse_iterator *ft_it3_reverse_const = &ft_it_reverse_const;
	std::map<std::string, std::string>::const_reverse_iterator *std_it3_reverse_const = &std_it_reverse_const;

	std::cout << "ft: *a: " << (*ft_it3_reverse_const)->first << std::endl;
	std::cout << "std: *a: " << (*std_it3_reverse_const)->first << std::endl << std::endl;

	std::cout << "ft: a++: " << (ft_it_reverse_const++)->first << std::endl;
	std::cout << "std: a++: " << (std_it_reverse_const++)->first << std::endl << std::endl;

	std::cout << "ft: ++a: " << (++ft_it_reverse_const)->first << std::endl;
	std::cout << "std: ++a: " << (++std_it_reverse_const)->first << std::endl << std::endl;

	std::cout << "ft: a--: " << (ft_it_reverse_const--)->first << std::endl;
	std::cout << "std: a--: " << (std_it_reverse_const--)->first << std::endl << std::endl;

	std::cout << "ft: --a: " << (--ft_it_reverse_const)->first << std::endl;
	std::cout << "std: --a: " << (--std_it_reverse_const)->first << std::endl << std::endl;

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

int main()
{
	map_iterator_tests();
	return 0;
}