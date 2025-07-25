#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include "set.hpp"
#include <set>

template<class T1>
void display_set_std(std::set<T1> std_vect)
{
	if (std_vect.size() > 0)
	{
		for (typename std::set<T1>::iterator it = std_vect.begin(); it != std_vect.end(); it++)
			std::cout << "std = " << *it << std::endl;
	}
	else
		std::cout << "Empty tree" << std::endl;
}

template<class T1>
void display_set_ft(ft::set<T1> ft_vect)
{
	if (ft_vect.size() > 0)
	{
		for (typename ft::set<T1>::iterator it = ft_vect.begin(); it != ft_vect.end(); it++)
			std::cout << "ft = " << *it << std::endl;
	}
	else
		std::cout << "Empty tree" << std::endl;
}

int main()
{
	std::cout << " ------------- CONSTRUCTORS AND OPERATOR[] ------------- " << std::endl << std::endl;

	std::cout << "--------------------------- ft --------------------------- \n";

	ft::set<int> ft_set;
	ft_set.insert(22);
	ft_set.insert(7777);
	ft_set.insert(44444);
	ft::set<int> ft_set2(ft_set.begin(), ft_set.end());
	display_set_ft(ft_set2);
	ft::set<int> ft_set3(ft_set2);

	std::cout << "ft: print set with copy constructor" << std::endl;
	display_set_ft(ft_set3);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::set<int> std_set;
	std_set.insert(22);
	std_set.insert(7777);
	std_set.insert(44444);
	std::set<int> std_set2(std_set.begin(), std_set.end());
	display_set_std(std_set2);
	std::set<int> std_set3(std_set2);

	std::cout << "std: print set with copy constructor" << std::endl;
	display_set_std(std_set3);

	std::cout << "--------------------------- OPERATOR= --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::set<int> ft_set4;
	ft_set4 = ft_set;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::set<int> std_set4;
	std_set4 = std_set;

	std::cout << "--------------------------- BEGIN --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::set<int>::iterator ft_it_set = ft_set.begin();
	ft::set<int>::const_iterator ft_it_set_const = ft_set.begin();

	std::cout << "ft iterator first = " << *ft_it_set << std::endl;
	std::cout << "ft const_iterator second = " << *ft_it_set_const << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::set<int>::iterator std_it_set = std_set.begin();
	std::set<int>::const_iterator std_it_set_const = std_set.begin();

	std::cout << "std iterator first = " << *std_it_set << std::endl;
	std::cout << "std const_iterator second = " << *std_it_set_const << std::endl;
	(void)std_it_set_const;

	std::cout << "--------------------------- END --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft_it_set = ft_set.end();
	ft_it_set_const = ft_set.end();

	std::cout << "ft iterator first = " << *ft_it_set << std::endl;
	std::cout << "ft const_iterator second = " << *ft_it_set_const << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std_it_set = std_set.end();
	std_it_set_const = std_set.end();

	std::cout << "std iterator first = " << *std_it_set << std::endl;
	std::cout << "std const_iterator second = " << *std_it_set_const << std::endl;
	(void)std_it_set_const;

	std::cout << "--------------------------- REVERSE BEGIN --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::set<int>::reverse_iterator ft_it_set_reverse = ft_set.rbegin();
	ft::set<int>::const_reverse_iterator ft_it_set_const_reverse = ft_set.rbegin();

	std::cout << "ft iterator_reverse first = " << *ft_it_set_reverse << std::endl;
	std::cout << "ft const_iterator_reverse second = " << *ft_it_set_const_reverse << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::set<int>::reverse_iterator std_it_set_reverse = std_set.rbegin();
	std::set<int>::const_reverse_iterator std_it_set_const_reverse = std_set.rbegin();

	std::cout << "std iterator_reverse first = " << *std_it_set_reverse << std::endl;
	std::cout << "std const_iterator_reverse second = " << *std_it_set_const_reverse << std::endl;
	(void)std_it_set_const_reverse;

	std::cout << "--------------------------- REVERSE END --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft_it_set_reverse = ft_set.rend();
	ft_it_set_const_reverse = ft_set.rend();

	std::cout << "ft iterator_reverse first = " << *ft_it_set_reverse << std::endl;
	std::cout << "ft const_iterator_reverse second = " << *ft_it_set_const_reverse << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std_it_set_reverse = std_set.rend();
	std_it_set_const_reverse = std_set.rend();

	std::cout << "std iterator_reverse first = " << *std_it_set_reverse << std::endl;
	std::cout << "std const_iterator_reverse second = " << *std_it_set_const_reverse << std::endl;
	(void)std_it_set_const_reverse;

	std::cout << "--------------------------- EMPTY --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::set<int> ft_set5;

	std::cout << "ft_set empty = " << ft_set.empty() << std::endl;
	std::cout << "ft_set5 empty = " << ft_set5.empty() << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::set<int> std_set5;

	std::cout << "std_set empty = " << std_set.empty() << std::endl;
	std::cout << "std_set5 empty = " << std_set5.empty() << std::endl;

	std::cout << "--------------------------- SIZE --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft_set size = " << ft_set.size() << std::endl;
	std::cout << "ft_set5 size = " << ft_set5.size() << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std_set size = " << std_set.size() << std::endl;
	std::cout << "std_set5 size = " << std_set5.size() << std::endl;

	std::cout << "--------------------------- MAX_SIZE --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft_set max_size = " << ft_set.max_size() << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std_set max_size = " << std_set.max_size() << std::endl;

	std::cout << " -------- INSERT (1st prototype) -------- " << std::endl << std::endl;

	std::cout << " --------------------------- FT --------------------------- " << std::endl << std::endl;
	ft::set<int> ft_insert;

	// first insert function version (single parameter):
	ft_insert.insert ( 100 );
	ft_insert.insert ( 200 );

	ft::pair<ft::set<int>::iterator,bool> ft_ret;
	ft_ret = ft_insert.insert ( 500 );
	if (ft_ret.second==false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << *ft_ret.first << '\n';
	}
	else if (ft_ret.second == true)
	{
		std::cout << "new element inserted";
		std::cout << " with a value of " << *ft_ret.first << '\n';
	}
	ft_ret = ft_insert.insert ( 500 );
	if (ft_ret.second==false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << *ft_ret.first << '\n';
	}
	else if (ft_ret.second == true)
	{
		std::cout << "new element inserted";
		std::cout << " with a value of " << *ft_ret.first << '\n';
	}

	std::cout << std::endl;

	std::cout << " --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::set<int> std_insert;

	// first insert function version (single parameter):
	std_insert.insert ( 100 );
	std_insert.insert ( 200 );

	std::pair<std::set<int>::iterator,bool> std_ret;
	std_ret = std_insert.insert ( 500 );
	if (std_ret.second==false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << *std_ret.first << '\n';
	}
	else if (std_ret.second == true)
	{
		std::cout << "new element inserted";
		std::cout << " with a value of " << *std_ret.first << '\n';
	}
	std_ret = std_insert.insert ( 500 );
	if (std_ret.second==false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << *std_ret.first << '\n';
	}
	else if (std_ret.second == true)
	{
		std::cout << "new element inserted";
		std::cout << " with a value of " << *std_ret.first << '\n';
	}
	std::cout << std::endl;

	std::cout << " -------- INSERT (2nd prototype) -------- " << std::endl << std::endl;

	std::cout << " --------------------------- FT --------------------------- " << std::endl;

	ft::set<int>::iterator it_ft2 = ft_insert.begin();
	std::cout << "\navant: \n";
	display_set_ft(ft_insert);
	ft_insert.insert (it_ft2, 300);
	ft::set<int>::iterator ft_it = ft_insert.insert (it_ft2, 400);
	std::cout << "\nreturn it = " << *ft_it << std::endl;
	std::cout << "\napres: \n";
	display_set_ft(ft_insert);
	ft_it = ft_insert.insert (it_ft2, 300);
	std::cout << "\nnode already in tree: \n";
	std::cout << "\nreturn it = " << *ft_it << std::endl << std::endl;
	display_set_ft(ft_insert);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl;
	
	std::set<int>::iterator it_std2 = std_insert.begin();
	std::cout << "\navant: \n";
	display_set_std(std_insert);
	std_insert.insert (it_std2, 300);
	std::set<int>::iterator std_it = std_insert.insert (it_std2, 400);
	std::cout << "\nreturn it = " << *std_it << std::endl;
	std::cout << "\napres: \n";
	display_set_std(std_insert);
	std_it = std_insert.insert (it_std2, 300);
	std::cout << "\nnode already in tree: \n";
	std::cout << "\nreturn it = " << *std_it << std::endl << std::endl;
	display_set_std(std_insert);
	
	std::cout << std::endl;

	std::cout << " -------- INSERT (3th prototype) -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft::set<int> anotherset_ft;
	anotherset_ft.insert(ft_insert.begin(), ft_insert.find(300));

	std::cout << "ft_insert contains:\n";
  	for (ft_it=ft_insert.begin(); ft_it!=ft_insert.end(); ++ft_it)
    	std::cout << *ft_it << '\n';

	std::cout << "anotherset_ft contains:\n";
  	for (ft_it=anotherset_ft.begin(); ft_it!=anotherset_ft.end(); ++ft_it)
    	std::cout << *ft_it << '\n';

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::set<int> anotherset_std;
	anotherset_std.insert(std_insert.begin(), std_insert.find(300));

	std::cout << "std_insert contains:\n";
  	for (std_it=std_insert.begin(); std_it!=std_insert.end(); ++std_it)
    	std::cout << *std_it << '\n';

	std::cout << "anotherset_std contains:\n";
  	for (std_it=anotherset_std.begin(); std_it!=anotherset_std.end(); ++std_it)
    	std::cout << *std_it << '\n';

	std::cout << " -------- ERASE (1st prototype) -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	std::cout << "avant ft:\n";
	display_set_ft(ft_insert);
	ft_insert.erase(ft_insert.find(300));
	std::cout << "\napres ft:\n";
	display_set_ft(ft_insert);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::cout << "avant std:\n";
	display_set_std(std_insert);
	std_insert.erase(std_insert.find(300));
	std::cout << "\napres std:\n";
	display_set_std(std_insert);

	std::cout << " -------- ERASE (2nd prototype) -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	std::cout << "avant ft:\n";
	display_set_ft(ft_insert);
	bool return_ft = ft_insert.erase(200);
	std::cout << "return ft = " << return_ft << std::endl;
	std::cout << "\napres ft:\n";
	display_set_ft(ft_insert);
	return_ft = ft_insert.erase(800);
	std::cout << "\nreturn ft non existant key = " << return_ft << std::endl;
	std::cout << "\napres ft:\n";
	display_set_ft(ft_insert);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::cout << "avant std:\n";
	display_set_std(std_insert);
	bool return_std = std_insert.erase(200);
	std::cout << "return std = " << return_std << std::endl;
	std::cout << "\napres std:\n";
	display_set_std(std_insert);
	return_std = std_insert.erase(800);
	std::cout << "\nreturn non existant key std = " << return_std << std::endl;
	std::cout << "\napres std:\n";
	display_set_std(std_insert);

	std::cout << " -------- ERASE (3rd prototype) -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	it_ft2 = ft_insert.begin();
	it_ft2++;
	std::cout << "ft avant: \n";
	display_set_ft(ft_insert);
	ft_insert.erase(it_ft2, ft_insert.end());
	std::cout << "\nft apres: \n";
	display_set_ft(ft_insert);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	it_std2 = std_insert.begin();
	it_std2++;
	std::cout << "std avant: \n";
	display_set_std(std_insert);
	std_insert.erase(it_std2, std_insert.end());
	std::cout << "\nstd apres: \n";
	display_set_std(std_insert);

	std::cout << "\n -------- SWAP -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft_insert.insert(200);
	ft_insert.insert(300);

	ft::set<int> ft_insert2;
	ft_insert2.insert(5555);
	ft_insert2.insert(6666);

	std::cout << "\nft first set before: \n";
	display_set_ft(ft_insert);
	std::cout << "\nft second set before: \n";
	display_set_ft(ft_insert2);

	ft_insert.swap(ft_insert2);
	std::cout << "\nft first set after: \n";
	display_set_ft(ft_insert);
	std::cout << "\nft second set after: \n";
	display_set_ft(ft_insert2);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std_insert.insert(200);
	std_insert.insert(300);

	std::set<int> std_insert2;
	std_insert2.insert(5555);
	std_insert2.insert(6666);

	std::cout << "\nstd first set before: \n";
	display_set_std(std_insert);
	std::cout << "\nstd second set before: \n";
	display_set_std(std_insert2);

	std_insert.swap(std_insert2);
	std::cout << "\nstd first set after: \n";
	display_set_std(std_insert);
	std::cout << "\nstd second set after: \n";
	display_set_std(std_insert2);

	std::cout << "\n -------- CLEAR -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	std::cout << "\nft set before: \n";
	display_set_ft(ft_insert2);
	ft_insert2.clear();
	std::cout << "\nft set after: \n";
	display_set_ft(ft_insert2);
	ft_insert2.clear();

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::cout << "\nstd set before: \n";
	display_set_std(std_insert2);
	std_insert2.clear();
	std::cout << "\nstd set astder: \n";
	display_set_std(std_insert2);
	std_insert2.clear();

	std::cout << "\n -------- KEY COMP -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft::set<int>::key_compare ft_my_comp = ft_insert.key_comp();
	ft_insert2.insert(777);
	ft_it = ft_insert2.begin();
	if (ft_my_comp((*ft_it), 777))
		std::cout << "FT PAREIL" << std::endl;
	else
		std::cout << "FT PAS PAREIL" << std::endl;
	
	std::cout << std::endl;
	if (ft_my_comp((*ft_it), 999))
		std::cout << "FT PAREIL" << std::endl;
	else
		std::cout << "FT PAS PAREIL" << std::endl;

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::set<int>::key_compare std_my_comp = std_insert.key_comp();
	std_insert2.insert(777);
	std_it = std_insert2.begin();
	if (std_my_comp((*std_it), 777))
		std::cout << "STD PAREIL" << std::endl;
	else
		std::cout << "STD PAS PAREIL" << std::endl;
	
	std::cout << std::endl;
	if (std_my_comp((*std_it), 999))
		std::cout << "STD PAREIL" << std::endl;
	else
		std::cout << "STD PAS PAREIL" << std::endl;

	std::cout << "\n -------- VALUE COMP -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft_insert.insert(999);

  	ft_it = ft_insert.begin();
	ft_it++;
	int ft_pair = *ft_insert.begin();

	if (ft_insert.value_comp()(*ft_it, ft_pair))
		std::cout << "STD PAREIL" << std::endl;
	else
		std::cout << "STD PAS PAREIL" << std::endl;

	ft_pair = *--ft_insert.end();

	std::cout << std::endl;
	if (ft_insert.value_comp()(*ft_it, ft_pair))
		std::cout << "STD PAREIL" << std::endl;
	else
		std::cout << "STD PAS PAREIL" << std::endl;

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std_insert.insert(999);

  	std_it = std_insert.begin();
	std_it++;
	int std_pair = *std_insert.begin();

	if (std_insert.value_comp()(*std_it, std_pair))
		std::cout << "STD PAREIL" << std::endl;
	else
		std::cout << "STD PAS PAREIL" << std::endl;

	std_pair = *--std_insert.end();

	std::cout << std::endl;
	if (std_insert.value_comp()(*std_it, std_pair))
		std::cout << "STD PAREIL" << std::endl;
	else
		std::cout << "STD PAS PAREIL" << std::endl;

	std::cout << "\n -------- FIND -------- " << std::endl << std::endl;

	ft_insert2.clear();
	std_insert2.clear();

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft_it = ft_insert.find(999);
	if (ft_it == ft_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << std::endl;

	ft_it = ft_insert.find(873);
	if (ft_it == ft_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std_it = std_insert.find(999);
	if (std_it == std_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << std::endl;

	std_it = std_insert.find(873);
	if (std_it == std_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << "\n -------- CONST IT FIND -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft::set<int>::const_iterator ft_it_const = ft_insert.find(999);
	if (ft_it_const == ft_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << std::endl;

	ft_it_const = ft_insert.find(873);
	if (ft_it_const == ft_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::set<int>::const_iterator std_it_const = std_insert.find(999);
	if (std_it_const == std_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << std::endl;

	std_it_const = std_insert.find(873);
	if (std_it_const == std_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << "\n -------- COUNT -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	std::cout << "sortie = " << ft_insert.count(999) << std::endl;
	std::cout << "sortie not found = " << ft_insert.count(873) << std::endl;

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::cout << "sortie = " << std_insert.count(999) << std::endl;
	std::cout << "sortie not found = " << std_insert.count(873) << std::endl;

	std::cout << "\n -------- LOWER BOUND -------- " << std::endl << std::endl;

	ft_insert.insert(745);
	std_insert.insert(745);

	for (int i = 0; i <= 999; i++)
	{
		// std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

		ft_it = ft_insert.lower_bound(i);
		// std::cout << "std = " << ft_it->first << std::endl;
		ft_it_const = ft_insert.lower_bound(i);
		// std::cout << "std const = " << ft_it_const->first << std::endl;

		// std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

		std_it = std_insert.lower_bound(i);
		// std::cout << "std = " << std_it->first << std::endl;
		std_it_const = std_insert.lower_bound(i);
		// std::cout << "std const = " << std_it_const->first << std::endl;

		if (*ft_it != *std_it && (*ft_it != 0 && *std_it != 4))
		{
			std::cout << "Y'A PROBLEME" << std::endl;
			break;
		}
	}

	std::cout << "lower bound tests ok" << std::endl;

	std::cout << "\n -------- UPPER BOUND -------- " << std::endl << std::endl;

	// display_set_ft(ft_insert);

	for (int i = 0; i <= 999; i++)
	{
		// std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;
		// display_set_ft(ft_insert);
		ft_it = ft_insert.upper_bound(i);
		// std::cout << "std = " << ft_it->first << std::endl;
		ft_it_const = ft_insert.upper_bound(i);
		// std::cout << "std const = " << ft_it_const->first << std::endl;

		// std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

		// display_set_std(std_insert);
		std_it = std_insert.upper_bound(i);
		// std::cout << "std = " << std_it->first << std::endl;
		std_it_const = std_insert.upper_bound(i);
		// std::cout << "std const = " << std_it_const->first << std::endl;

		if (*ft_it != *std_it && (*ft_it != 0 && *std_it != 4))
		{
			std::cout << "Y'A PROBLEME" << std::endl;
			break;
		}
	}

	std::cout << "upper bound tests ok" << std::endl;

	std::cout << "\n -------- EQUAL RANGE -------- " << std::endl << std::endl;


	for (int i = 0; i <= 999; i++)
	{
		// std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

		// display_set_ft(ft_insert);
		ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> ft_ret2;
		ft_ret2 = ft_insert.equal_range(i);
		// std::cout << "lower bound points to: ";
		// std::cout << ft_ret2.first->first << " => " << ft_ret2.first->second << '\n';

		// std::cout << "upper bound points to: ";
		// std::cout << ft_ret2.second->first << " => " << ft_ret2.second->second << '\n';

		// std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

		// display_set_std(std_insert);
		std::pair<std::set<int>::iterator, std::set<int>::iterator> std_ret2;
		std_ret2 = std_insert.equal_range(i);
		// std::cout << "lower bound points to: ";
		// std::cout << std_ret2.first->first << " => " << std_ret2.first->second << '\n';

		// std::cout << "upper bound points to: ";
		// std::cout << std_ret2.second->first << " => " << std_ret2.second->second << '\n';

		if ((*ft_ret2.first != *std_ret2.first && (*ft_ret2.first != 0 && *std_ret2.first != 4))
			&& (*ft_ret2.second != *std_ret2.second && (*ft_ret2.second != 0 && *std_ret2.second != 4)))
		{
			std::cout << "Y'A PROBLEME" << std::endl;
			break;
		}
	}

	std::cout << "equal range tests ok" << std::endl;

	std::cout << "\n -------- CONST EQUAL RANGE -------- " << std::endl << std::endl;

	for (int i = 0; i <= 999; i++)
	{
		// std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

		// display_map_ft(ft_insert);
		ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> ft_ret2_const;
		ft_ret2_const = ft_insert.equal_range(i);
		// std::cout << "lower bound points to: ";
		// std::cout << ft_ret2_const.first->first << " => " << ft_ret2_const.first->second << '\n';

		// std::cout << "upper bound points to: ";
		// std::cout << ft_ret2_const.second->first << " => " << ft_ret2_const.second->second << '\n';

		// std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

		// display_map_std(std_insert);

		std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> std_ret2_const;
		std_ret2_const = std_insert.equal_range(i);
		// std::cout << "lower bound points to: ";
		// std::cout << std_ret2_const.first->first << " => " << std_ret2_const.first->second << '\n';

		// std::cout << "upper bound points to: ";
		// std::cout << std_ret2_const.second->first << " => " << std_ret2_const.second->second << '\n';

		if ((*ft_ret2_const.first != *std_ret2_const.first && (*ft_ret2_const.first != 0 && *std_ret2_const.first != 4))
			&& (*ft_ret2_const.second != *std_ret2_const.second && (*ft_ret2_const.second != 0 && *std_ret2_const.second != 4)))
		{
			std::cout << "Y'A PROBLEME" << std::endl;
			break;
		}
	}

	std::cout << "const equal range tests ok" << std::endl;

	std::cout << "\n -------- GET_ALLOCATOR -------- " << std::endl << std::endl;

	std::cout << "\n -------- FT -------- " << std::endl << std::endl;

	int ft_psize;
	int* ft_p;

	ft_p = ft_set.get_allocator().allocate(5);

	ft_psize = sizeof(ft::set<int>::value_type)*5;

	std::cout << "The allocated array has a size of " << ft_psize << " bytes.\n";

	ft_set.get_allocator().deallocate(ft_p, 5);

	std::cout << "\n -------- STD -------- " << std::endl << std::endl;

	int std_psize;
	int* std_p;

	std_p = std_set.get_allocator().allocate(5);

	std_psize = sizeof(std::set<int>::value_type)*5;

	std::cout << "The allocated array has a size of " << std_psize << " bytes.\n";

	std_set.get_allocator().deallocate(std_p, 5);

	return 0;
};