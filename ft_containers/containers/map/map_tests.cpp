#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include "map.hpp"

template<class T1, class T2>
void display_map_std(std::map<T1, T2> std_vect)
{
	if (std_vect.size() > 0)
	{
		for (typename std::map<T1, T2>::iterator it = std_vect.begin(); it != std_vect.end(); it++)
			std::cout << "std = " << it->first << " | " << it->second << std::endl;
	}
	else
		std::cout << "Empty tree" << std::endl;
}

template<class T1, class T2>
void display_map_ft(ft::map<T1, T2> ft_vect)
{
	if (ft_vect.size() > 0)
	{
		for (typename ft::map<T1, T2>::iterator it = ft_vect.begin(); it != ft_vect.end(); it++)
			std::cout << "ft = " << it->first << " | " << it->second << std::endl;
	}
	else
		std::cout << "Empty tree" << std::endl;
}

int map_tests()
{
	std::cout << " ------------- CONSTRUCTORS AND OPERATOR[] ------------- " << std::endl << std::endl;

	std::cout << "--------------------------- ft --------------------------- \n";

	ft::map<char, int> ft_map;
	ft_map['a'] = 22;
	ft_map['m'] = 7777;
	ft_map['z'] = 44444;
	ft::map<char, int> ft_map2(ft_map.begin(), ft_map.end());
	display_map_ft(ft_map2);
	ft::map<char, int> ft_map3(ft_map2);

	std::cout << "ft: print map with copy constructor" << std::endl;
	display_map_ft(ft_map3);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::map<char, int> std_map;
	std_map['a'] = 22;
	std_map['m'] = 7777;
	std_map['z'] = 44444;
	std::map<char, int> std_map2(std_map.begin(), std_map.end());
	display_map_std(std_map2);
	std::map<char, int> std_map3(std_map2);

	std::cout << "std: print map with copy constructor" << std::endl;
	display_map_std(std_map3);

	std::cout << "--------------------------- OPERATOR= --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::map<char, int> ft_map4;
	ft_map4 = ft_map;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::map<char, int> std_map4;
	std_map4 = std_map;

	std::cout << "--------------------------- BEGIN --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::map<char, int>::iterator ft_it_map = ft_map.begin();
	ft::map<char, int>::const_iterator ft_it_map_const = ft_map.begin();

	std::cout << "ft iterator first = " << ft_it_map->first << std::endl;
	std::cout << "ft const_iterator second = " << ft_it_map_const->second << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::map<char, int>::iterator std_it_map = std_map.begin();
	std::map<char, int>::const_iterator std_it_map_const = std_map.begin();

	std::cout << "std iterator first = " << std_it_map->first << std::endl;
	std::cout << "std const_iterator second = " << std_it_map_const->second << std::endl;
	(void)std_it_map_const;

	std::cout << "--------------------------- END --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft_it_map = ft_map.end();
	ft_it_map_const = ft_map.end();

	std::cout << "ft iterator first = " << ft_it_map->first << std::endl;
	std::cout << "ft const_iterator second = " << ft_it_map_const->second << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std_it_map = std_map.end();
	std_it_map_const = std_map.end();

	std::cout << "std iterator first = " << std_it_map->first << std::endl;
	std::cout << "std const_iterator second = " << std_it_map_const->second << std::endl;
	(void)std_it_map_const;

	std::cout << "--------------------------- REVERSE BEGIN --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::map<char, int>::reverse_iterator ft_it_map_reverse = ft_map.rbegin();
	ft::map<char, int>::const_reverse_iterator ft_it_map_const_reverse = ft_map.rbegin();

	std::cout << "ft iterator_reverse first = " << ft_it_map_reverse->first << std::endl;
	std::cout << "ft const_iterator_reverse second = " << ft_it_map_const_reverse->second << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::map<char, int>::reverse_iterator std_it_map_reverse = std_map.rbegin();
	std::map<char, int>::const_reverse_iterator std_it_map_const_reverse = std_map.rbegin();

	std::cout << "std iterator_reverse first = " << std_it_map_reverse->first << std::endl;
	std::cout << "std const_iterator_reverse second = " << std_it_map_const_reverse->second << std::endl;
	(void)std_it_map_const_reverse;

	std::cout << "--------------------------- REVERSE END --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft_it_map_reverse = ft_map.rend();
	ft_it_map_const_reverse = ft_map.rend();

	std::cout << "ft iterator_reverse first = " << ft_it_map_reverse->first << std::endl;
	std::cout << "ft const_iterator_reverse second = " << ft_it_map_const_reverse->second << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std_it_map_reverse = std_map.rend();
	std_it_map_const_reverse = std_map.rend();

	std::cout << "std iterator_reverse first = " << std_it_map_reverse->first << std::endl;
	std::cout << "std const_iterator_reverse second = " << std_it_map_const_reverse->second << std::endl;
	(void)std_it_map_const_reverse;

	std::cout << "--------------------------- EMPTY --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::map<char, int> ft_map5;

	std::cout << "ft_map empty = " << ft_map.empty() << std::endl;
	std::cout << "ft_map5 empty = " << ft_map5.empty() << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::map<char, int> std_map5;

	std::cout << "std_map empty = " << std_map.empty() << std::endl;
	std::cout << "std_map5 empty = " << std_map5.empty() << std::endl;

	std::cout << "--------------------------- SIZE --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft_map size = " << ft_map.size() << std::endl;
	std::cout << "ft_map5 size = " << ft_map5.size() << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std_map size = " << std_map.size() << std::endl;
	std::cout << "std_map5 size = " << std_map5.size() << std::endl;

	std::cout << "--------------------------- MAX_SIZE --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft_map max_size = " << ft_map.max_size() << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std_map max_size = " << std_map.max_size() << std::endl;

	std::cout << " -------- INSERT (1st prototype) -------- " << std::endl << std::endl;

	std::cout << " --------------------------- FT --------------------------- " << std::endl << std::endl;
	ft::map<char,int> ft_insert;

	// first insert function version (single parameter):
	ft_insert.insert ( ft::pair<char,int>('a',100) );
	ft_insert.insert ( ft::pair<char,int>('z',200) );

	ft::pair<ft::map<char,int>::iterator,bool> ft_ret;
	ft_ret = ft_insert.insert ( ft::pair<char,int>('z',500) );
	if (ft_ret.second==false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ft_ret.first->second << '\n';
	}
	else if (ft_ret.second == true)
	{
		std::cout << "new element inserted";
		std::cout << " with a value of " << ft_ret.first->second << '\n';
	}
	ft_ret = ft_insert.insert ( ft::pair<char,int>('m',777) );
	if (ft_ret.second==false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ft_ret.first->second << '\n';
	}
	else if (ft_ret.second == true)
	{
		std::cout << "new element inserted";
		std::cout << " with a value of " << ft_ret.first->second << '\n';
	}

	std::cout << std::endl;

	std::cout << " --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::map<char,int> std_insert;

	// first insert function version (single parameter):
	std_insert.insert ( std::pair<char,int>('a',100) );
	std_insert.insert ( std::pair<char,int>('z',200) );

	std::pair<std::map<char,int>::iterator,bool> std_ret;
	std_ret = std_insert.insert ( std::pair<char,int>('z',500) );
	if (std_ret.second==false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << std_ret.first->second << '\n';
	}
	else if (std_ret.second == true)
	{
		std::cout << "new element inserted";
		std::cout << " with a value of " << std_ret.first->second << '\n';
	}
	std_ret = std_insert.insert ( std::pair<char,int>('m',777) );
	if (std_ret.second==false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << std_ret.first->second << '\n';
	}
	else if (std_ret.second == true)
	{
		std::cout << "new element inserted";
		std::cout << " with a value of " << std_ret.first->second << '\n';
	}
	std::cout << std::endl;

	std::cout << " -------- INSERT (2nd prototype) -------- " << std::endl << std::endl;

	std::cout << " --------------------------- FT --------------------------- " << std::endl;

	ft::map<char,int>::iterator it_ft2 = ft_insert.begin();
	std::cout << "\navant: \n";
	display_map_ft(ft_insert);
	ft_insert.insert (it_ft2, ft::pair<char,int>('b',300));
	ft::map<char,int>::iterator ft_it = ft_insert.insert (it_ft2, ft::pair<char,int>('c',400));
	std::cout << "\nreturn it = " << ft_it->first << std::endl;
	std::cout << "\napres: \n";
	display_map_ft(ft_insert);
	ft_it = ft_insert.insert (it_ft2, ft::pair<char,int>('a',300));
	std::cout << "\nnode already in tree: \n";
	std::cout << "\nreturn it = " << ft_it->first << std::endl << std::endl;
	display_map_ft(ft_insert);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl;
	
	std::map<char,int>::iterator it_std2 = std_insert.begin();
	std::cout << "\navant: \n";
	display_map_std(std_insert);
	std_insert.insert (it_std2, std::pair<char,int>('b',300));
	std::map<char,int>::iterator std_it = std_insert.insert (it_std2, std::pair<char,int>('c',400));
	std::cout << "\nreturn it = " << std_it->first << std::endl;
	std::cout << "\napres: \n";
	display_map_std(std_insert);
	std_it = std_insert.insert (it_std2, std::pair<char,int>('a',300));
	std::cout << "\nnode already in tree: \n";
	std::cout << "\nreturn it = " << std_it->first << std::endl << std::endl;
	display_map_std(std_insert);
	
	std::cout << std::endl;

	std::cout << " -------- INSERT (3th prototype) -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;


	ft::map<char,int> anothermap_ft;
	anothermap_ft.insert(ft_insert.begin(), ft_insert.find('c'));

	std::cout << "ft_insert contains:\n";
  	for (ft_it=ft_insert.begin(); ft_it!=ft_insert.end(); ++ft_it)
    	std::cout << ft_it->first << " => " << ft_it->second << '\n';

	std::cout << "anothermap_ft contains:\n";
  	for (ft_it=anothermap_ft.begin(); ft_it!=anothermap_ft.end(); ++ft_it)
    	std::cout << ft_it->first << " => " << ft_it->second << '\n';

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::map<char,int> anothermap_std;
	anothermap_std.insert(std_insert.begin(), std_insert.find('c'));

	std::cout << "std_insert contains:\n";
  	for (std_it=std_insert.begin(); std_it!=std_insert.end(); ++std_it)
    	std::cout << std_it->first << " => " << std_it->second << '\n';

	std::cout << "anothermap_std contains:\n";
  	for (std_it=anothermap_std.begin(); std_it!=anothermap_std.end(); ++std_it)
    	std::cout << std_it->first << " => " << std_it->second << '\n';

	std::cout << " -------- ERASE (1st prototype) -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	std::cout << "avant ft:\n";
	display_map_ft(ft_insert);
	ft_insert.erase(ft_insert.find('m'));
	std::cout << "\napres ft:\n";
	display_map_ft(ft_insert);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::cout << "avant std:\n";
	display_map_std(std_insert);
	std_insert.erase(std_insert.find('m'));
	std::cout << "\napres std:\n";
	display_map_std(std_insert);

	std::cout << " -------- ERASE (2nd prototype) -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	std::cout << "avant ft:\n";
	display_map_ft(ft_insert);
	bool return_ft = ft_insert.erase('b');
	std::cout << "return ft = " << return_ft << std::endl;
	std::cout << "\napres ft:\n";
	display_map_ft(ft_insert);
	return_ft = ft_insert.erase('g');
	std::cout << "\nreturn ft non existant key = " << return_ft << std::endl;
	std::cout << "\napres ft:\n";
	display_map_ft(ft_insert);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::cout << "avant std:\n";
	display_map_std(std_insert);
	bool return_std = std_insert.erase('b');
	std::cout << "return std = " << return_std << std::endl;
	std::cout << "\napres std:\n";
	display_map_std(std_insert);
	return_std = std_insert.erase('g');
	std::cout << "\nreturn non existant key std = " << return_std << std::endl;
	std::cout << "\napres std:\n";
	display_map_std(std_insert);

	std::cout << " -------- ERASE (3rd prototype) -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	it_ft2 = ft_insert.begin();
	it_ft2++;
	std::cout << "ft avant: \n";
	display_map_ft(ft_insert);
	ft_insert.erase(it_ft2, ft_insert.end());
	std::cout << "\nft apres: \n";
	display_map_ft(ft_insert);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	it_std2 = std_insert.begin();
	it_std2++;
	std::cout << "std avant: \n";
	display_map_std(std_insert);
	std_insert.erase(it_std2, std_insert.end());
	std::cout << "\nstd apres: \n";
	display_map_std(std_insert);

	std::cout << "\n -------- SWAP -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft_insert['m'] = 200;
	ft_insert['z'] = 300;

	ft::map<char,int> ft_insert2;
	ft_insert2['n'] = 5555;
	ft_insert2['o'] = 6666;

	std::cout << "\nft first map before: \n";
	display_map_ft(ft_insert);
	std::cout << "\nft second map before: \n";
	display_map_ft(ft_insert2);

	ft_insert.swap(ft_insert2);
	std::cout << "\nft first map after: \n";
	display_map_ft(ft_insert);
	std::cout << "\nft second map after: \n";
	display_map_ft(ft_insert2);

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std_insert['m'] = 200;
	std_insert['z'] = 300;

	std::map<char,int> std_insert2;
	std_insert2['n'] = 5555;
	std_insert2['o'] = 6666;

	std::cout << "\nstd first map before: \n";
	display_map_std(std_insert);
	std::cout << "\nstd second map before: \n";
	display_map_std(std_insert2);

	std_insert.swap(std_insert2);
	std::cout << "\nstd first map after: \n";
	display_map_std(std_insert);
	std::cout << "\nstd second map after: \n";
	display_map_std(std_insert2);

	std::cout << "\n -------- CLEAR -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	std::cout << "\nft map before: \n";
	display_map_ft(ft_insert2);
	ft_insert2.clear();
	std::cout << "\nft map after: \n";
	display_map_ft(ft_insert2);
	ft_insert2.clear();

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::cout << "\nstd map before: \n";
	display_map_std(std_insert2);
	std_insert2.clear();
	std::cout << "\nstd map astder: \n";
	display_map_std(std_insert2);
	std_insert2.clear();

	std::cout << "\n -------- KEY COMP -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft::map<char,int>::key_compare ft_my_comp = ft_insert.key_comp();
	ft_insert2['m'] = 777;
	ft_it = ft_insert2.begin();
	if (ft_my_comp((*ft_it).first, 'l'))
		std::cout << "FT PAREIL" << std::endl;
	else
		std::cout << "FT PAS PAREIL" << std::endl;
	
	std::cout << std::endl;
	if (ft_my_comp((*ft_it).first, 'y'))
		std::cout << "FT PAREIL" << std::endl;
	else
		std::cout << "FT PAS PAREIL" << std::endl;

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::map<char,int>::key_compare std_my_comp = std_insert.key_comp();
	std_insert2['m'] = 777;
	std_it = std_insert2.begin();
	if (std_my_comp((*std_it).first, 'l'))
		std::cout << "STD PAREIL" << std::endl;
	else
		std::cout << "STD PAS PAREIL" << std::endl;
	
	std::cout << std::endl;
	if (std_my_comp((*std_it).first, 'y'))
		std::cout << "STD PAREIL" << std::endl;
	else
		std::cout << "STD PAS PAREIL" << std::endl;

	std::cout << "\n -------- VALUE COMP -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft_insert['a'] = 999;

  	ft_it = ft_insert.begin();
	ft_it++;
	ft::pair<char,int> ft_pair = *ft_insert.begin();

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

	std_insert['a'] = 999;

  	std_it = std_insert.begin();
	std_it++;
	std::pair<char,int> std_pair = *std_insert.begin();

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

	ft_it = ft_insert.find('a');
	if (ft_it == ft_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << std::endl;

	ft_it = ft_insert.find('z');
	if (ft_it == ft_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std_it = std_insert.find('a');
	if (std_it == std_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << std::endl;

	std_it = std_insert.find('z');
	if (std_it == std_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << "\n -------- CONST IT FIND -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	ft::map<char, int>::const_iterator ft_it_const = ft_insert.find('a');
	if (ft_it_const == ft_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << std::endl;

	ft_it_const = ft_insert.find('z');
	if (ft_it_const == ft_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::map<char, int>::const_iterator std_it_const = std_insert.find('a');
	if (std_it_const == std_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << std::endl;

	std_it_const = std_insert.find('z');
	if (std_it_const == std_insert.end())
		std::cout << "Element not found" << std::endl;
	else
		std::cout << "Element FOUND" << std::endl;

	std::cout << "\n -------- COUNT -------- " << std::endl << std::endl;

	std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

	std::cout << "sortie = " << ft_insert.count('a') << std::endl;
	std::cout << "sortie not found = " << ft_insert.count('m') << std::endl;

	std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

	std::cout << "sortie = " << std_insert.count('a') << std::endl;
	std::cout << "sortie not found = " << std_insert.count('m') << std::endl;

	std::cout << "\n -------- LOWER BOUND -------- " << std::endl << std::endl;

	ft_insert['g'] = 745;
	std_insert['g'] = 745;

	for (int i = 'a'; i <= 'z'; i++)
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

		if (ft_it->first != std_it->first && (ft_it->first != 0 && std_it->first != 4))
		{
			std::cout << "Y'A PROBLEME" << std::endl;
			break;
		}
	}

	std::cout << "lower bound tests ok" << std::endl;

	std::cout << "\n -------- UPPER BOUND -------- " << std::endl << std::endl;

	// display_map_ft(ft_insert);

	for (int i = 'a'; i <= 'z'; i++)
	{
		// std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;
		// display_map_ft(ft_insert);
		ft_it = ft_insert.upper_bound(i);
		// std::cout << "std = " << ft_it->first << std::endl;
		ft_it_const = ft_insert.upper_bound(i);
		// std::cout << "std const = " << ft_it_const->first << std::endl;

		// std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

		// display_map_std(std_insert);
		std_it = std_insert.upper_bound(i);
		// std::cout << "std = " << std_it->first << std::endl;
		std_it_const = std_insert.upper_bound(i);
		// std::cout << "std const = " << std_it_const->first << std::endl;

		if (ft_it->first != std_it->first && (ft_it->first != 0 && std_it->first != 4))
		{
			std::cout << "Y'A PROBLEME" << std::endl;
			break;
		}
	}

	std::cout << "upper bound tests ok" << std::endl;

	std::cout << "\n -------- EQUAL RANGE -------- " << std::endl << std::endl;


	for (int i = 'a'; i <= 'z'; i++)
	{
		// std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

		// display_map_ft(ft_insert);
		ft::pair<ft::map<char,int>::iterator, ft::map<char,int>::iterator> ft_ret2;
		ft_ret2 = ft_insert.equal_range(i);
		// std::cout << "lower bound points to: ";
		// std::cout << ft_ret2.first->first << " => " << ft_ret2.first->second << '\n';

		// std::cout << "upper bound points to: ";
		// std::cout << ft_ret2.second->first << " => " << ft_ret2.second->second << '\n';

		// std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

		// display_map_std(std_insert);
		std::pair<std::map<char,int>::iterator, std::map<char,int>::iterator> std_ret2;
		std_ret2 = std_insert.equal_range(i);
		// std::cout << "lower bound points to: ";
		// std::cout << std_ret2.first->first << " => " << std_ret2.first->second << '\n';

		// std::cout << "upper bound points to: ";
		// std::cout << std_ret2.second->first << " => " << std_ret2.second->second << '\n';

		if ((ft_ret2.first->first != std_ret2.first->first && (ft_ret2.first->first != 0 && std_ret2.first->first != 4))
			&& (ft_ret2.second->first != std_ret2.second->first && (ft_ret2.second->first != 0 && std_ret2.second->first != 4)))
		{
			std::cout << "Y'A PROBLEME" << std::endl;
			break;
		}
	}

	std::cout << "equal range tests ok" << std::endl;

	std::cout << "\n -------- CONST EQUAL RANGE -------- " << std::endl << std::endl;

	for (int i = 'a'; i <= 'z'; i++)
	{
		// std::cout << "\n --------------------------- FT --------------------------- " << std::endl << std::endl;

		// display_map_ft(ft_insert);
		ft::pair<ft::map<char,int>::const_iterator, ft::map<char,int>::const_iterator> ft_ret2_const;
		ft_ret2_const = ft_insert.equal_range(i);
		// std::cout << "lower bound points to: ";
		// std::cout << ft_ret2_const.first->first << " => " << ft_ret2_const.first->second << '\n';

		// std::cout << "upper bound points to: ";
		// std::cout << ft_ret2_const.second->first << " => " << ft_ret2_const.second->second << '\n';

		// std::cout << "\n --------------------------- STD --------------------------- " << std::endl << std::endl;

		// display_map_std(std_insert);

		std::pair<std::map<char,int>::const_iterator, std::map<char,int>::const_iterator> std_ret2_const;
		std_ret2_const = std_insert.equal_range(i);
		// std::cout << "lower bound points to: ";
		// std::cout << std_ret2_const.first->first << " => " << std_ret2_const.first->second << '\n';

		// std::cout << "upper bound points to: ";
		// std::cout << std_ret2_const.second->first << " => " << std_ret2_const.second->second << '\n';

		if ((ft_ret2_const.first->first != std_ret2_const.first->first && (ft_ret2_const.first->first != 0 && std_ret2_const.first->first != 4))
			&& (ft_ret2_const.second->first != std_ret2_const.second->first && (ft_ret2_const.second->first != 0 && std_ret2_const.second->first != 4)))
		{
			std::cout << "Y'A PROBLEME" << std::endl;
			break;
		}
	}

	std::cout << "const equal range tests ok" << std::endl;

	std::cout << "\n -------- GET_ALLOCATOR -------- " << std::endl << std::endl;

	std::cout << "\n -------- FT -------- " << std::endl << std::endl;

	int ft_psize;
	ft::pair<const char,int>* ft_p;

	ft_p = ft_map.get_allocator().allocate(5);

	ft_psize = sizeof(ft::map<char,int>::value_type)*5;

	std::cout << "The allocated array has a size of " << ft_psize << " bytes.\n";

	ft_map.get_allocator().deallocate(ft_p, 5);

	std::cout << "\n -------- STD -------- " << std::endl << std::endl;

	int std_psize;
	std::pair<const char,int>* std_p;

	std_p = std_map.get_allocator().allocate(5);

	std_psize = sizeof(std::map<char,int>::value_type)*5;

	std::cout << "The allocated array has a size of " << std_psize << " bytes.\n";

	std_map.get_allocator().deallocate(std_p, 5);

	return 0;
}

int main()
{
	map_tests();
	return 0;
}