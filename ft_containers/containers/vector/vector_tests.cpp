#include "vector.hpp"
#include <vector>
#include <iostream>
#include "Traits.hpp"

void print_info_std(std::vector<int> std_vect)
{
	std::cout << "----------------------------- Contenu std -----------------------------" << std::endl;
	for (std::vector<int>::size_type i = 0; i < std_vect.size(); ++i)
		std::cout << *(std_vect.begin() + i) << std::endl;	
}

void print_info_ft(ft::vector<int> ft_vect)
{
	std::cout << "----------------------------- Contenu ft -----------------------------" << std::endl;
	for (ft::vector<int>::size_type i = 0; i < ft_vect.size(); ++i)
		std::cout << *(ft_vect.begin() + i) << std::endl;	
}

int	vector_tests()
{
	std::cout << "--------------------------- VECTOR TESTS --------------------------- \n";
	std::cout << "--------------------------- CONSTRUCTOR --------------------------- \n";

	std::cout << "--------------------------- ft --------------------------- \n";

	ft::vector<int> ft_vector;
	ft::vector<int> ft_vector2(4, 777);
	ft::vector<int>::iterator ft_it_vect_begin = ft_vector2.begin();
	ft::vector<int>::iterator ft_it_vect_end = ft_vector2.end();
	ft::vector<int> ft_vector3(ft_it_vect_begin, ft_it_vect_end);
	ft_vector3.push_back(1234);

	ft::vector<int> ft_vector4(ft_vector);
	ft::vector<int> ft_vector5(ft_vector2);

	print_info_ft(ft_vector4);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::vector<int> std_vector;
	std::vector<int> std_vector2(4, 777);
	std::vector<int>::iterator std_it_vect_begin = std_vector2.begin();
	std::vector<int>::iterator std_it_vect_end = std_vector2.end();
	std::vector<int> std_vector3(std_it_vect_begin, std_it_vect_end);
	std_vector3.push_back(1234);

	std::vector<int> std_vector4(std_vector);
	std::vector<int> std_vector5(std_vector2);

	print_info_std(std_vector4);

	std::cout << "--------------------------- OPERATOR= --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft_vector = ft_vector3;
	print_info_ft(ft_vector);

	std::cout << "--------------------------- STD --------------------------- \n";

	std_vector = std_vector3;
	print_info_std(std_vector);

	std::cout << "--------------------------- BEGIN AND END --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::vector<int>::iterator ft_it_begin = ft_vector.begin();
	ft::vector<int>::const_iterator ft_it_begin_const = ft_vector.begin();
	ft::vector<int>::iterator ft_it_end = ft_vector.end();
	ft::vector<int>::const_iterator ft_it_end_const = ft_vector.end();

	std::cout << "--------------------------- STD --------------------------- \n";

	std::vector<int>::iterator std_it_begin = std_vector.begin();
	std::vector<int>::const_iterator std_it_begin_const = std_vector.begin();
	std::vector<int>::iterator std_it_end = std_vector.end();
	std::vector<int>::const_iterator std_it_end_const = std_vector.end();
	(void)std_it_begin;
	(void)std_it_begin_const;
	(void)std_it_end;
	(void)std_it_end_const;

	std::cout << "--------------------------- REVERSE BEGIN AND END --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::vector<int>::reverse_iterator ft_it_begin_reverse = ft_vector.rbegin();
	ft::vector<int>::const_reverse_iterator ft_it_begin_reverse_const = ft_vector.rbegin();
	ft::vector<int>::reverse_iterator ft_it_end_reverse = ft_vector.rend();
	ft::vector<int>::const_reverse_iterator ft_it_end_reverse_const = ft_vector.rend();

	std::cout << "--------------------------- STD --------------------------- \n";

	std::vector<int>::reverse_iterator std_it_begin_reverse = std_vector.rbegin();
	std::vector<int>::const_reverse_iterator std_it_begin_reverse_const = std_vector.rbegin();
	std::vector<int>::reverse_iterator std_it_end_reverse = std_vector.rend();
	std::vector<int>::const_reverse_iterator std_it_end_reverse_const = std_vector.rend();
	(void)std_it_begin_reverse;
	(void)std_it_begin_reverse_const;
	(void)std_it_end_reverse;
	(void)std_it_end_reverse_const;

	std::cout << "--------------------------- CAPACITY FUNCTIONS --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft size = " << ft_vector.size() << std::endl;
	std::cout << "ft max_size = " << ft_vector.max_size() << std::endl;
	std::cout << "ft resize before less = " << std::endl;
	print_info_ft(ft_vector);
	ft_vector.resize(2);
	std::cout << "ft resize after less = " << std::endl;
	print_info_ft(ft_vector);
	std::cout << "ft resize before more = " << std::endl;
	print_info_ft(ft_vector);
	ft_vector.resize(4);
	std::cout << "ft resize after more = " << std::endl;
	print_info_ft(ft_vector);
	std::cout << "ft capacity = " << ft_vector.capacity() << std::endl;
	std::cout << "ft empty = " << ft_vector.empty() << std::endl;

	std::cout << "ft reserve before less = " << ft_vector.capacity() << std::endl;
	ft_vector.reserve(1);
	std::cout << "ft reserve after less = " << ft_vector.capacity() << std::endl;
	std::cout << "ft reserve before more = " << ft_vector.capacity() << std::endl;
	ft_vector.reserve(10);
	std::cout << "ft reserve after more = " << ft_vector.capacity() << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std size = " << std_vector.size() << std::endl;
	std::cout << "std max_size = " << std_vector.max_size() << std::endl;
	std::cout << "std resize before less = " << std::endl;
	print_info_std(std_vector);
	std_vector.resize(2);
	std::cout << "std resize after less = " << std::endl;
	print_info_std(std_vector);
	std::cout << "std resize before more = " << std::endl;
	print_info_std(std_vector);
	std_vector.resize(4);
	std::cout << "std resize after more = " << std::endl;
	print_info_std(std_vector);
	std::cout << "std capacity = " << std_vector.capacity() << std::endl;
	std::cout << "std empty = " << std_vector.empty() << std::endl;

	std::cout << "std reserve before less = " << std_vector.capacity() << std::endl;
	std_vector.reserve(1);
	std::cout << "std reserve after less = " << std_vector.capacity() << std::endl;
	std::cout << "std reserve before more = " << std_vector.capacity() << std::endl;
	std_vector.reserve(10);
	std::cout << "std reserve after more = " << std_vector.capacity() << std::endl;

	std::cout << "--------------------------- ELEMENT ACCESS FUNCTIONS --------------------------- \n";

	std::cout << "--------------------------- operator[] --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft id 0 = " << ft_vector[0] << std::endl;
	std::cout << "ft id 3 = " << ft_vector[3] << std::endl;
	try
	{
		std::cout << "ft id 4 = " << ft_vector[4] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::cout << "ft id -1 = " << ft_vector[-1] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	ft::vector<int>::const_reference ft_const_ref = ft_vector[0];
	try
	{
		ft::vector<int>::const_reference ft_const_ref2 = ft_vector[-1];
		(void)ft_const_ref2;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	(void)ft_const_ref;
	
	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std id 0 = " << std_vector[0] << std::endl;
	std::cout << "std id 3 = " << std_vector[3] << std::endl;
	// segfault sur std -> normal
	try
	{
		// std::cout << "std id 4 = " << std_vector[4] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		// std::cout << "std id -1 = " << std_vector[-1] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::vector<int>::const_reference std_const_ref = std_vector[0];
	try
	{
		// std::vector<int>::const_reference std_const_ref2 = std_vector[-1];
		// (void)std_const_ref2;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	(void)std_const_ref;

	std::cout << "--------------------------- AT --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft id 0 = " << ft_vector.at(0) << std::endl;
	std::cout << "ft id 3 = " << ft_vector.at(3) << std::endl;
	try
	{
		std::cout << "ft id 4 = " << ft_vector.at(4) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::cout << "ft id -1 = " << ft_vector.at(-1) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	ft::vector<int>::const_reference ft_const_ref_at = ft_vector.at(0);
	try
	{
		ft::vector<int>::const_reference ft_const_ref_at2 = ft_vector.at(-1);
		(void)ft_const_ref_at2;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	(void)ft_const_ref_at;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std id 0 = " << std_vector.at(0) << std::endl;
	std::cout << "std id 3 = " << std_vector.at(3) << std::endl;
	try
	{
		std::cout << "std id 4 = " << std_vector.at(4) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::cout << "std id -1 = " << std_vector.at(-1) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::vector<int>::const_reference std_const_ref_at = std_vector.at(0);
	try
	{
		std::vector<int>::const_reference std_const_ref_at2 = std_vector.at(-1);
		(void)std_const_ref_at2;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	(void)std_const_ref_at;

	std::cout << "--------------------------- FRONT --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::vector<int> ft_vector_front;
	try
	{
		std::cout << "ft front empty vector = " << ft_vector_front.front() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "ft front = " << ft_vector.front() << std::endl;

	try
	{
		ft::vector<int>::const_reference ft_front_const_ref = ft_vector_front.front();
		std::cout << "ft front empty vector const ref = " << ft_front_const_ref << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	ft::vector<int>::const_reference ft_front_const_ref2 = ft_vector.front();
	std::cout << "ft front empty vector const ref = " << ft_front_const_ref2 << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	std::vector<int> std_vector_front;
	try
	{
		// std::cout << "std front empty vector = " << std_vector_front.front() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "std front = " << std_vector.front() << std::endl;

	try
	{
		// std::vector<int>::const_reference std_front_const_ref = std_vector_front.front();
		// std::cout << "std front empty vector const ref = " << std_front_const_ref << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::vector<int>::const_reference std_front_const_ref2 = std_vector.front();
	std::cout << "std front empty vector const ref = " << std_front_const_ref2 << std::endl;

	std::cout << "--------------------------- BACK --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	try
	{
		std::cout << "ft back empty vector = " << ft_vector_front.back() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "ft back = " << ft_vector.back() << std::endl;

	try
	{
		ft::vector<int>::const_reference ft_back_const_ref = ft_vector_front.back();
		std::cout << "ft front empty vector const ref = " << ft_back_const_ref << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	ft::vector<int>::const_reference ft_back_const_ref2 = ft_vector.back();
	std::cout << "ft front empty vector const ref = " << ft_back_const_ref2 << std::endl;

	std::cout << "--------------------------- STD --------------------------- \n";

	try
	{
		// std::cout << "std back empty vector = " << std_vector_front.back() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "std back = " << std_vector.back() << std::endl;

	try
	{
		// std::vector<int>::const_reference std_back_const_ref = std_vector_front.back();
		// std::cout << "front empty vector const ref = " << std_back_const_ref << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::vector<int>::const_reference std_back_const_ref2 = std_vector.back();
	std::cout << "front empty vector const ref = " << std_back_const_ref2 << std::endl;

	std::cout << "--------------------------- ASSIGN --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft assign 1st prototype:\n";
	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);
	ft_vector.assign(ft_vector3.begin() + 1, ft_vector3.end());
	std::cout << "ft vector apres:\n";
	print_info_ft(ft_vector);
	std::cout << "ft assign 2nd prototype:\n";
	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);
	ft_vector.assign(2, 33);
	std::cout << "ft vector apres:\n";
	print_info_ft(ft_vector);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std assign 1st prototype:\n";
	std::cout << "std vector avant:\n";
	print_info_std(std_vector);
	std_vector.assign(std_vector3.begin() + 1, std_vector3.end());
	std::cout << "std vector apres:\n";
	print_info_std(std_vector);
	std::cout << "std assign 2nd prototype:\n";
	std::cout << "std vector avant:\n";
	print_info_std(std_vector);
	std_vector.assign(2, 33);
	std::cout << "std vector apres:\n";
	print_info_std(std_vector);

	std::cout << "--------------------------- PUSH_BACK --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);
	ft_vector.push_back(6543);
	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std vector avant:\n";
	print_info_std(std_vector);
	std_vector.push_back(6543);
	std::cout << "std vector avant:\n";
	print_info_std(std_vector);

	std::cout << "--------------------------- POP_BACK --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);
	ft_vector.pop_back();
	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std vector avant:\n";
	print_info_std(std_vector);
	std_vector.pop_back();
	std::cout << "std vector avant:\n";
	print_info_std(std_vector);

	std::cout << "--------------------------- INSERT --------------------------- \n";

	std::cout << "--------------------------- 1st prototype --------------------------- \n";
	std::cout << "--------------------------- FT --------------------------- \n";


	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);
	ft_vector.insert(ft_vector.begin() + 1, 8765);
	std::cout << "ft vector apres:\n";
	print_info_ft(ft_vector);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std vector avant:\n";
	print_info_std(std_vector);
	std_vector.insert(std_vector.begin() + 1, 8765);
	std::cout << "std vector apres:\n";
	print_info_std(std_vector);

	std::cout << "--------------------------- 2nd prototype --------------------------- \n";
	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);
	ft_vector.insert(ft_vector.begin() + 2, 3, 40004);
	std::cout << "ft vector apres:\n";
	print_info_ft(ft_vector);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std vector avant:\n";
	print_info_std(std_vector);
	std_vector.insert(std_vector.begin() + 2, 3, 40004);
	std::cout << "std vector apres:\n";
	print_info_std(std_vector);

	std::cout << "--------------------------- 3rd prototype --------------------------- \n";
	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);
	ft_vector.insert(ft_vector.begin() + 3, ft_vector.begin(), ft_vector.begin() + 2);
	std::cout << "ft vector apres:\n";
	print_info_ft(ft_vector);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std vector avant:\n";
	print_info_std(std_vector);
	std_vector.insert(std_vector.begin() + 3, std_vector.begin(), std_vector.begin() + 2);
	std::cout << "std vector apres:\n";
	print_info_std(std_vector);

	std::cout << "--------------------------- ERASE --------------------------- \n";
	std::cout << "--------------------------- 1st prototype --------------------------- \n";
	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);
	ft_vector.erase(ft_vector.begin() + 3);
	std::cout << "ft vector apres:\n";
	print_info_ft(ft_vector);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std vector avant:\n";
	print_info_std(std_vector);
	std_vector.erase(std_vector.begin() + 3);
	std::cout << "std vector apres:\n";
	print_info_std(std_vector);

	std::cout << "--------------------------- 2nd prototype --------------------------- \n";
	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector);
	ft_vector.erase(ft_vector.begin() + 3, ft_vector.begin() + 6);
	std::cout << "ft vector apres:\n";
	print_info_ft(ft_vector);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std vector avant:\n";
	print_info_std(std_vector);
	std_vector.erase(std_vector.begin() + 3, std_vector.begin() + 6);
	std::cout << "std vector apres:\n";
	print_info_std(std_vector);

	std::cout << "--------------------------- SWAP --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft 1st vector avant:\n";
	print_info_ft(ft_vector);
	std::cout << "ft 2nd vector avant:\n";
	print_info_ft(ft_vector2);

	ft_vector.swap(ft_vector2);
	std::cout << "ft 1st vector apres:\n";
	print_info_ft(ft_vector);
	std::cout << "ft 2nd vector apres:\n";
	print_info_ft(ft_vector2);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std 1st vector avant:\n";
	print_info_std(std_vector);
	std::cout << "std 2nd vector avant:\n";
	print_info_std(std_vector2);

	std_vector.swap(std_vector2);
	std::cout << "std 1st vector apres:\n";
	print_info_std(std_vector);
	std::cout << "std 2nd vector apres:\n";
	print_info_std(std_vector2);

	std::cout << "--------------------------- CLEAR --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	std::cout << "ft vector avant:\n";
	print_info_ft(ft_vector2);
	ft_vector2.clear();
	std::cout << "ft vector apres:\n";
	print_info_ft(ft_vector2);

	std::cout << "--------------------------- STD --------------------------- \n";

	std::cout << "std vector avant:\n";
	print_info_std(std_vector2);
	std_vector2.clear();
	std::cout << "std vector apres:\n";
	print_info_std(std_vector2);


	std::cout << "--------------------------- Non-member function overloads --------------------------- \n";

	std::cout << "--------------------------- relational operators --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";

	ft::vector<int> foo_ft (3,100);   // three ints with a value of 100
  	ft::vector<int> bar_ft (2,200);   // two ints with a value of 200

	if (foo_ft==bar_ft) std::cout << "ft: foo and bar are equal\n";
	if (foo_ft!=bar_ft) std::cout << "ft: foo and bar are not equal\n";
	if (foo_ft< bar_ft) std::cout << "ft: foo is less than bar\n";
	if (foo_ft> bar_ft) std::cout << "ft: foo is greater than bar\n";
	if (foo_ft<=bar_ft) std::cout << "ft: foo is less than or equal to bar\n";
	if (foo_ft>=bar_ft) std::cout << "ft: foo is greater than or equal to bar\n";
	
	std::cout << "--------------------------- STD --------------------------- \n";

	std::vector<int> foo_std (3,100);   // three ints with a value of 100
  	std::vector<int> bar_std (2,200);   // two ints with a value of 200

	if (foo_std==bar_std) std::cout << "std: foo and bar are equal\n";
	if (foo_std!=bar_std) std::cout << "std: foo and bar are not equal\n";
	if (foo_std< bar_std) std::cout << "std: foo is less than bar\n";
	if (foo_std> bar_std) std::cout << "std: foo is greater than bar\n";
	if (foo_std<=bar_std) std::cout << "std: foo is less than or equal to bar\n";
	if (foo_std>=bar_std) std::cout << "std: foo is greater than or equal to bar\n";

	std::cout << "--------------------------- SWAP --------------------------- \n";

	std::cout << "--------------------------- FT --------------------------- \n";
	ft_vector2.push_back(9271);
	std::cout << "ft vector 1 before:" << std::endl;
	print_info_ft(ft_vector);
	std::cout << "ft vector 2 before:" << std::endl;
	print_info_ft(ft_vector2);

	ft::swap(ft_vector, ft_vector2);

	std::cout << "ft vector 1 after:" << std::endl;
	print_info_ft(ft_vector);
	std::cout << "ft vector 2 after:" << std::endl;
	print_info_ft(ft_vector2);
	std::cout << "--------------------------- STD --------------------------- \n";

	return 0;
}

int main()
{
	vector_tests();
	return 0;
}