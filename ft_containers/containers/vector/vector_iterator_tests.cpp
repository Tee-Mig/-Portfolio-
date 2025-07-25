#include "vector.hpp"
#include <vector>

int	vector_iterator_tests()
{
	std::cout << "------------------ normal iterator tests ------------------" << std::endl << std::endl;
	// test iterator
	ft::vector<int> ft_vect(10);
	std::vector<int> std_vect(10);

	ft::vector<int>::iterator it1;
	ft::vector<int>::iterator it2(it1);
	it2 = it1;

	// operator[] that fill vector
	for (int i = 0; i < 10; i++)
	{
		ft_vect[i] = i * 5;
		std_vect[i] = i * 5;
	}

	ft::vector<int>::iterator it_begin_ft = ft_vect.begin();
	ft::vector<int>::iterator it_end_ft = ft_vect.end();

	std::vector<int>::iterator it_begin_std = std_vect.begin();
	std::vector<int>::iterator it_end_std = std_vect.end();

	(void)it_end_std;
	(void)it_end_ft;
	(void)it_begin_std;
	(void)it_begin_ft;


	std::cout << "ft: print fill vector with [] (*a)" << std::endl;
	for (ft::vector<int>::iterator it = it_begin_ft; it != it_end_ft; ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	
	std::cout << "std: print fill vector with [] (*a)" << std::endl;
	for (std::vector<int>::iterator it = it_begin_std; it != it_end_std; ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	if (it_begin_ft != it_end_ft)
		std::cout << "ft: pas pareil\n";
	if (it_begin_ft == it_begin_ft)
		std::cout << "ft: pareil\n";
	if (it_begin_ft <= it_begin_ft)
		std::cout << "ft: pareil\n";
	if (it_begin_ft >= it_begin_ft)
		std::cout << "ft: pareil\n";
	if (it_begin_ft < it_begin_ft)
		std::cout << "ft: pareil\n";
	if (it_begin_ft > it_begin_ft)
		std::cout << "ft: pareil\n";


	if (it_begin_std != it_end_std)
		std::cout << "std: pas pareil\n";
	if (it_begin_std == it_begin_std)
		std::cout << "std: pareil\n";
	if (it_begin_std <= it_begin_std)
		std::cout << "std: pareil\n";
	if (it_begin_std >= it_begin_std)
		std::cout << "std: pareil\n";
	if (it_begin_std < it_begin_std)
		std::cout << "std: pareil\n";
	if (it_begin_std > it_begin_std)
		std::cout << "std: pareil\n";

	std::cout << std::endl;

	*it_begin_ft = 777;
	*it_begin_std = 777;

	std::cout << "ft: *a = t" << std::endl;
	std::cout << *it_begin_ft << std::endl << std::endl;

	std::cout << "std: *a = t" << std::endl;
	std::cout << *it_begin_std << std::endl << std::endl;

	// a++
	std::cout << "ft: a++" << std::endl;
	std::cout << *it_begin_ft++ << std::endl;
	std::cout << *it_begin_ft << std::endl << std::endl;

	std::cout << "std: a++" << std::endl;
	std::cout << *it_begin_std++ << std::endl;
	std::cout << *it_begin_std << std::endl << std::endl;

	std::cout << "ft: ++a" << std::endl;
	std::cout << *(++it_begin_ft) << std::endl << std::endl;

	std::cout << "std: ++a" << std::endl;
	std::cout << *(++it_begin_std) << std::endl << std::endl;

	// a--
	std::cout << "ft: a--" << std::endl;
	std::cout << *it_begin_ft-- << std::endl;
	std::cout << *it_begin_ft << std::endl << std::endl;

	std::cout << "std: a--" << std::endl;
	std::cout << *it_begin_std-- << std::endl;
	std::cout << *it_begin_std << std::endl << std::endl;

	std::cout << "ft: --a" << std::endl;
	std::cout << *(--it_begin_ft) << std::endl << std::endl;

	std::cout << "std: --a" << std::endl;
	std::cout << *(--it_begin_std) << std::endl << std::endl;

	// a + n
	it_begin_ft = it_begin_ft + 7;
	std::cout << "ft: a + n" << std::endl;
	std::cout << *it_begin_ft << std::endl << std::endl;

	it_begin_std = it_begin_std + 7;
	std::cout << "std: a + n" << std::endl;
	std::cout << *it_begin_std << std::endl << std::endl;

	// a - n
	it_begin_ft = it_begin_ft - 7;
	std::cout << "ft: a - n" << std::endl;
	std::cout << *it_begin_ft << std::endl << std::endl;

	it_begin_std = it_begin_std - 7;
	std::cout << "std: a - n" << std::endl;
	std::cout << *it_begin_std << std::endl << std::endl;

	// a += n
	std::cout << "ft: a += n" << std::endl;
	it_begin_ft += 6;
	std::cout << *it_begin_ft << std::endl << std::endl;

	it_begin_std += 6;
	std::cout << "std: a += n" << std::endl;
	std::cout << *it_begin_std << std::endl << std::endl;

	it_begin_ft -= 6;
	std::cout << "ft: a -= n" << std::endl;
	std::cout << *it_begin_ft << std::endl << std::endl;

	it_begin_std -= 6;
	std::cout << "std: a -= n" << std::endl;
	std::cout << *it_begin_std << std::endl << std::endl;

	// operator <, <=, >, >=
	std::cout << "Operator <, <=, >, >=" << std::endl << std::endl;
	std::cout << "ft: " << std::endl;
	if (*it_begin_ft >= *it_begin_ft)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft > *it_begin_ft)
		std::cout << "False" << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std >= *it_begin_std)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std > *it_begin_std)
		std::cout << "False" << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "ft: " << std::endl;
	if (*it_begin_ft <= *it_begin_ft)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft < *it_begin_ft)
		std::cout << "False" << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std <= *it_begin_std)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std < *it_begin_std)
		std::cout << "False" << std::endl;
	else
		std::cout << "True" << std::endl;
	
	

	std::cout << "------------------ const iterator tests ------------------" << std::endl << std::endl;

	// test iterator
	ft::vector<int> ft_vect_const(10);
	std::vector<int> std_vect_const(10);

	ft::vector<int>::const_iterator it1_const;
	ft::vector<int>::const_iterator it2_const(it1_const);
	it2_const = it1_const;

	// operator[] that fill vector
	for (int i = 0; i < 10; i++)
	{
		ft_vect_const[i] = i * 5;
		std_vect_const[i] = i * 5;
	}

	ft::vector<int>::const_iterator it_begin_ft_const = ft_vect_const.begin();
	ft::vector<int>::const_iterator it_end_ft_const = ft_vect_const.end();

	std::vector<int>::const_iterator it_begin_std_const = std_vect_const.begin();
	std::vector<int>::const_iterator it_end_std_const = std_vect_const.end();

	(void)it_end_std_const;
	(void)it_end_ft_const;
	(void)it_begin_std_const;
	(void)it_begin_ft_const;

	if (it_begin_std == it_begin_std_const)
		std::cout << "TRUEEE\n";
	else
		std::cout << "FALSE\n";

	std::cout << "ft: print fill vector with [] (*a)" << std::endl;
	for (ft::vector<int>::const_iterator it = it_begin_ft_const; it != it_end_ft_const; ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	
	std::cout << "std: print fill vector with [] (*a)" << std::endl;
	for (std::vector<int>::const_iterator it = it_begin_std_const; it != it_end_std_const; ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	if (it_begin_ft_const != it_end_ft_const)
		std::cout << "ft: pas pareil\n";
	if (it_begin_ft_const == it_begin_ft_const)
		std::cout << "ft: pareil\n";

	if (it_begin_std_const != it_end_std)
		std::cout << "std: pas pareil\n";
	if (it_begin_std_const == it_begin_std_const)
		std::cout << "std: pareil\n";

	std::cout << std::endl;

	// *it_begin_ft_const = 777;
	// *it_begin_std_const = 777;

	std::cout << "ft: *a = t" << std::endl;
	std::cout << *it_begin_ft_const << std::endl << std::endl;

	std::cout << "std: *a = t" << std::endl;
	std::cout << *it_begin_std_const << std::endl << std::endl;

	// a++
	std::cout << "ft: a++" << std::endl;
	std::cout << *it_begin_ft_const++ << std::endl;
	std::cout << *it_begin_ft_const << std::endl << std::endl;

	std::cout << "std: a++" << std::endl;
	std::cout << *it_begin_std_const++ << std::endl;
	std::cout << *it_begin_std_const << std::endl << std::endl;

	std::cout << "ft: ++a" << std::endl;
	std::cout << *(++it_begin_ft_const) << std::endl << std::endl;

	std::cout << "std: ++a" << std::endl;
	std::cout << *(++it_begin_std_const) << std::endl << std::endl;

	// a--
	std::cout << "ft: a--" << std::endl;
	std::cout << *it_begin_ft_const-- << std::endl;
	std::cout << *it_begin_ft_const << std::endl << std::endl;

	std::cout << "std: a--" << std::endl;
	std::cout << *it_begin_std_const-- << std::endl;
	std::cout << *it_begin_std_const << std::endl << std::endl;

	std::cout << "ft: --a" << std::endl;
	std::cout << *(--it_begin_ft_const) << std::endl << std::endl;

	std::cout << "std: --a" << std::endl;
	std::cout << *(--it_begin_std_const) << std::endl << std::endl;

	// a + n
	it_begin_ft_const = it_begin_ft_const + 7;
	std::cout << "ft: a + n" << std::endl;
	std::cout << *it_begin_ft_const << std::endl << std::endl;

	it_begin_std_const = it_begin_std_const + 7;
	std::cout << "std: a + n" << std::endl;
	std::cout << *it_begin_std_const << std::endl << std::endl;

	// a - n
	it_begin_ft_const = it_begin_ft_const - 7;
	std::cout << "ft: a - n" << std::endl;
	std::cout << *it_begin_ft_const << std::endl << std::endl;

	it_begin_std_const = it_begin_std_const - 7;
	std::cout << "std: a - n" << std::endl;
	std::cout << *it_begin_std_const << std::endl << std::endl;

	// a += n
	std::cout << "ft: a += n" << std::endl;
	it_begin_ft_const += 6;
	std::cout << *it_begin_ft_const << std::endl << std::endl;

	it_begin_std_const += 6;
	std::cout << "std: a += n" << std::endl;
	std::cout << *it_begin_std_const << std::endl << std::endl;

	it_begin_ft_const -= 6;
	std::cout << "ft: a -= n" << std::endl;
	std::cout << *it_begin_ft_const << std::endl << std::endl;

	it_begin_std_const -= 6;
	std::cout << "std: a -= n" << std::endl;
	std::cout << *it_begin_std_const << std::endl << std::endl;

	// operator <, <=, >, >=
	std::cout << "Operator <, <=, >, >=" << std::endl << std::endl;
	std::cout << "ft: " << std::endl;
	if (*it_begin_ft_const >= *it_begin_ft_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft_const > *it_begin_ft_const)
		std::cout << "False" << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std_const >= *it_begin_std_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std_const > *it_begin_std_const)
		std::cout << "False" << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "ft: " << std::endl;
	if (*it_begin_ft_const <= *it_begin_ft_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft_const < *it_begin_ft_const)
		std::cout << "False" << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std_const <= *it_begin_std_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std_const < *it_begin_std_const)
		std::cout << "False" << std::endl;
	else
		std::cout << "True" << std::endl;

	std::cout << " ---------------------------- Operators between iterator and const_iterator ---------------------------- " << std::endl;

	if (it_begin_ft == it_begin_ft_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std == it_begin_std_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft != it_begin_ft_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std != it_begin_std_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft <= it_begin_ft_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std <= it_begin_std_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft >= it_begin_ft_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std >= it_begin_std_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft < it_begin_ft_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std < it_begin_std_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft > it_begin_ft_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std > it_begin_std_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << "------------------ reverse iterator tests ------------------" << std::endl;

	ft::vector<int>::reverse_iterator it_begin_ft_rev = ft_vect.rbegin();
	ft::vector<int>::reverse_iterator it_end_ft_rev = ft_vect.rend();

	std::vector<int>::reverse_iterator it_begin_std_rev = std_vect.rbegin();
	std::vector<int>::reverse_iterator it_end_std_rev = std_vect.rend();
	(void)it_begin_ft_rev;
	(void)it_end_ft_rev;
	(void)it_begin_std_rev;
	(void)it_end_std_rev;

	it_end_ft_rev -= 1;
	it_end_std_rev -= 1;
	std::cout << "ft = " << *it_end_ft_rev << std::endl;
	std::cout << "std = " << *it_end_std_rev << std::endl;

	std::cout << std::endl;

	it_begin_ft_rev += 1;
	it_begin_std_rev += 1;
	std::cout << "ft = " << *it_begin_ft_rev << std::endl;
	std::cout << "std = " << *it_begin_std_rev << std::endl;

	std::cout << std::endl;

	std::cout << "ft: " << std::endl;
	if (it_begin_ft_rev != it_end_ft_rev)
		std::cout << "pas pareil\n";
	if (it_begin_ft_rev == it_begin_ft_rev)
		std::cout << "pareil\n";
	if (it_begin_ft_rev <= it_begin_ft_rev)
		std::cout << "pareil\n";
	if (it_begin_ft_rev >= it_begin_ft_rev)
		std::cout << "pareil\n";
	if (it_begin_ft_rev < it_begin_ft_rev)
		std::cout << "pareil\n";
	if (it_begin_ft_rev > it_begin_ft_rev)
		std::cout << "pareil\n";
	std::cout << std::endl;

	std::cout << "std: " << std::endl;
	if (it_begin_std_rev != it_end_std_rev)
		std::cout << "pas pareil\n";
	if (it_begin_std_rev == it_begin_std_rev)
		std::cout << "pareil\n";
	if (it_begin_std_rev <= it_begin_std_rev)
		std::cout << "pareil\n";
	if (it_begin_std_rev >= it_begin_std_rev)
		std::cout << "pareil\n";
	if (it_begin_std_rev < it_begin_std_rev)
		std::cout << "pareil\n";
	if (it_begin_std_rev > it_begin_std_rev)
		std::cout << "pareil\n";
	std::cout << std::endl;

	*it_begin_ft_rev = 777;
	*it_begin_std_rev = 777;

	std::cout << "ft: *a = t" << std::endl;
	std::cout << *it_begin_ft_rev << std::endl << std::endl;

	std::cout << "std: *a = t" << std::endl;
	std::cout << *it_begin_std_rev << std::endl << std::endl;

	// a++
	std::cout << "ft: a++" << std::endl;
	std::cout << *it_begin_ft_rev++ << std::endl << std::endl;

	std::cout << "std: a++" << std::endl;
	std::cout << *it_begin_std_rev++ << std::endl << std::endl;

	// ++a
	std::cout << "ft: ++a" << std::endl;
	std::cout << *++it_begin_ft_rev << std::endl << std::endl;

	std::cout << "std: ++a" << std::endl;
	std::cout << *++it_begin_std_rev << std::endl << std::endl;

	// a--
	std::cout << "ft: a--" << std::endl;
	std::cout << *it_begin_ft_rev-- << std::endl << std::endl;

	std::cout << "std: a--" << std::endl;
	std::cout << *it_begin_std_rev-- << std::endl << std::endl;

	// --a
	std::cout << "ft: --a" << std::endl;
	std::cout << *(--it_begin_ft_rev) << std::endl << std::endl;

	std::cout << "std: --a" << std::endl;
	std::cout << *(--it_begin_std_rev) << std::endl << std::endl;

	// a + n
	it_begin_ft_rev = it_begin_ft_rev + 7;
	std::cout << "ft: a + n" << std::endl;
	std::cout << *it_begin_ft_rev << std::endl << std::endl;

	it_begin_std_rev = it_begin_std_rev + 7;
	std::cout << "std: a + n" << std::endl;
	std::cout << *it_begin_std_rev << std::endl << std::endl;

	// a - n
	it_begin_ft_rev = it_begin_ft_rev - 6;
	std::cout << "ft: a - n" << std::endl;
	std::cout << *it_begin_ft_rev << std::endl << std::endl;

	it_begin_std_rev = it_begin_std_rev - 6;
	std::cout << "std: a - n" << std::endl;
	std::cout << *it_begin_std_rev << std::endl << std::endl;

	// a += n
	std::cout << "ft: a += n" << std::endl;
	it_begin_ft_rev += 6;
	std::cout << *it_begin_ft_rev << std::endl << std::endl;

	it_begin_std_rev += 6;
	std::cout << "std: a += n" << std::endl;
	std::cout << *it_begin_std_rev << std::endl << std::endl;

	// a -= n
	it_begin_ft_rev -= 6;
	std::cout << "ft: a -= n" << std::endl;
	std::cout << *it_begin_ft_rev << std::endl << std::endl;

	it_begin_std_rev -= 6;
	std::cout << "std: a -= n" << std::endl;
	std::cout << *it_begin_std_rev << std::endl << std::endl;

	// relational operators
	std::cout << "Relational operators:" << std::endl << std::endl;
	std::cout << "ft: " << std::endl;
	if (*it_begin_ft_rev == *it_begin_ft_rev)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft_rev != *it_begin_ft_rev)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std_rev == *it_begin_std_rev)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std_rev != *it_begin_std_rev)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "ft: " << std::endl;
	if (*it_begin_ft_rev > *it_begin_ft_rev)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft_rev >= *it_begin_ft_rev)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std_rev > *it_begin_std_rev)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std_rev >= *it_begin_std_rev)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "ft: " << std::endl;
	if (*it_begin_ft_rev < *it_begin_ft_rev)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft_rev <= *it_begin_ft_rev)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std_rev < *it_begin_std_rev)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std_rev <= *it_begin_std_rev)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	
	std::cout << "------------------ const reverse iterator tests ------------------" << std::endl;

	ft::vector<int>::const_reverse_iterator it_begin_ft_rev_const = ft_vect.rbegin();
	ft::vector<int>::const_reverse_iterator it_end_ft_rev_const = ft_vect.rend();

	std::vector<int>::const_reverse_iterator it_begin_std_rev_const = std_vect.rbegin();
	std::vector<int>::const_reverse_iterator it_end_std_rev_const = std_vect.rend();
	(void)it_begin_ft_rev_const;
	(void)it_end_ft_rev_const;
	(void)it_begin_std_rev_const;
	(void)it_end_std_rev_const;

	it_end_ft_rev_const -= 1;
	it_end_std_rev_const -= 1;
	std::cout << "ft = " << *it_end_ft_rev_const << std::endl;
	std::cout << "std = " << *it_end_std_rev_const << std::endl;

	std::cout << std::endl;

	it_begin_ft_rev_const += 1;
	it_begin_std_rev_const += 1;
	std::cout << "ft = " << *it_begin_ft_rev_const << std::endl;
	std::cout << "std = " << *it_begin_std_rev_const << std::endl;

	std::cout << std::endl;

	if (it_begin_ft_rev_const != it_end_ft_rev_const)
		std::cout << "pas pareil\n";
	if (it_begin_ft_rev_const == it_begin_ft_rev_const)
		std::cout << "pareil\n";
	std::cout << std::endl;

	if (it_begin_std_rev_const != it_end_std_rev_const)
		std::cout << "pas pareil\n";
	if (it_begin_std_rev_const == it_begin_std_rev_const)
		std::cout << "pareil\n";
	std::cout << std::endl;

	// *it_begin_ft_rev_const = 777;
	// *it_begin_std_rev_const = 777;

	std::cout << "ft: *a = t" << std::endl;
	std::cout << *it_begin_ft_rev_const << std::endl << std::endl;

	std::cout << "std: *a = t" << std::endl;
	std::cout << *it_begin_std_rev_const << std::endl << std::endl;

	// a++
	std::cout << "ft: a++" << std::endl;
	std::cout << *it_begin_ft_rev_const++ << std::endl << std::endl;

	std::cout << "std: a++" << std::endl;
	std::cout << *it_begin_std_rev_const++ << std::endl << std::endl;

	// ++a
	std::cout << "ft: ++a" << std::endl;
	std::cout << *++it_begin_ft_rev_const << std::endl << std::endl;

	std::cout << "std: ++a" << std::endl;
	std::cout << *++it_begin_std_rev_const << std::endl << std::endl;

	// a--
	std::cout << "ft: a--" << std::endl;
	std::cout << *it_begin_ft_rev_const-- << std::endl << std::endl;

	std::cout << "std: a--" << std::endl;
	std::cout << *it_begin_std_rev_const-- << std::endl << std::endl;

	// --a
	std::cout << "ft: --a" << std::endl;
	std::cout << *(--it_begin_ft_rev_const) << std::endl << std::endl;

	std::cout << "std: --a" << std::endl;
	std::cout << *(--it_begin_std_rev_const) << std::endl << std::endl;

	// a + n
	it_begin_ft_rev_const = it_begin_ft_rev_const + 7;
	std::cout << "ft: a + n" << std::endl;
	std::cout << *it_begin_ft_rev_const << std::endl << std::endl;

	it_begin_std_rev_const = it_begin_std_rev_const + 7;
	std::cout << "std: a + n" << std::endl;
	std::cout << *it_begin_std_rev_const << std::endl << std::endl;

	// a - n
	it_begin_ft_rev_const = it_begin_ft_rev_const - 6;
	std::cout << "ft: a - n" << std::endl;
	std::cout << *it_begin_ft_rev_const << std::endl << std::endl;

	it_begin_std_rev_const = it_begin_std_rev_const - 6;
	std::cout << "std: a - n" << std::endl;
	std::cout << *it_begin_std_rev_const << std::endl << std::endl;

	// a += n
	std::cout << "ft: a += n" << std::endl;
	it_begin_ft_rev_const += 6;
	std::cout << *it_begin_ft_rev_const << std::endl << std::endl;

	it_begin_std_rev_const += 6;
	std::cout << "std: a += n" << std::endl;
	std::cout << *it_begin_std_rev_const << std::endl << std::endl;

	// a -= n
	it_begin_ft_rev_const -= 6;
	std::cout << "ft: a -= n" << std::endl;
	std::cout << *it_begin_ft_rev_const << std::endl << std::endl;

	it_begin_std_rev_const -= 6;
	std::cout << "std: a -= n" << std::endl;
	std::cout << *it_begin_std_rev_const << std::endl << std::endl;

	// relational operators
	std::cout << "Relational operators:" << std::endl << std::endl;
	std::cout << "ft: " << std::endl;
	if (*it_begin_ft_rev_const == *it_begin_ft_rev_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft_rev_const != *it_begin_ft_rev_const)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std_rev_const == *it_begin_std_rev_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std_rev_const != *it_begin_std_rev_const)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "ft: " << std::endl;
	if (*it_begin_ft_rev_const > *it_begin_ft_rev_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft_rev_const >= *it_begin_ft_rev_const)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std_rev_const > *it_begin_std_rev_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std_rev_const >= *it_begin_std_rev_const)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "ft: " << std::endl;
	if (*it_begin_ft_rev_const < *it_begin_ft_rev_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_ft_rev_const <= *it_begin_ft_rev_const)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << "std: " << std::endl;
	if (*it_begin_std_rev_const < *it_begin_std_rev_const)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	if (*it_begin_std_rev_const <= *it_begin_std_rev_const)
		std::cout << "False" << std::endl << std::endl;
	else
		std::cout << "True" << std::endl << std::endl;

	std::cout << " ---------------------------- Operators between reverse_iterator and const_reverse_iterator ---------------------------- " << std::endl;

	if (it_begin_ft_rev == it_begin_ft_rev_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std_rev == it_begin_std_rev_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft_rev != it_begin_ft_rev_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std_rev != it_begin_std_rev_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft_rev <= it_begin_ft_rev_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std_rev <= it_begin_std_rev_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft_rev >= it_begin_ft_rev_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std_rev >= it_begin_std_rev_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft_rev < it_begin_ft_rev_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std_rev < it_begin_std_rev_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	std::cout << std::endl;

	if (it_begin_ft_rev > it_begin_ft_rev_const)
		std::cout << "ft: pareil\n";
	else
		std::cout << "ft: pas pareil\n";

	if (it_begin_std_rev > it_begin_std_rev_const)
		std::cout << "std: pareil\n";
	else
		std::cout << "std: pas pareil\n";

	return 0;
}

int main()
{
	vector_iterator_tests();
	return 0;
}