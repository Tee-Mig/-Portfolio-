#include "../inc/main.hpp"
#define K 10000
#include <set>
#include <stack>

int	main()
{
	std::cout << " ------------------------ VECTOR BIG INSERT ------------------------ " << std::endl << std::endl;

	ft::vector<int> m1_vector;
    unsigned int j = 0;
	clock_t begin_time_vector = clock();
    while ( j < K ){
        m1_vector.insert(m1_vector.end(), j);
        j++;
    }
	float ft_time_vector = float(clock () - begin_time_vector) /  CLOCKS_PER_SEC;
	std::cout << "temps ft = " << ft_time_vector << std::endl;

	std::vector<int> m2_vector;
    j = 0;
	begin_time_vector = clock();
    while ( j < K ){
        m2_vector.insert(m2_vector.end(), j);
        j++;
    }
	float std_time_vector = float(clock () - begin_time_vector) /  CLOCKS_PER_SEC;
	std::cout << "temps std = " << std_time_vector << std::endl;

	std::cout << "ft est " << ft_time_vector / std_time_vector << "x plus lent que le vrai container" << std::endl;

	std::cout << " ------------------------ VECTOR BIG ITERATOR ------------------------ " << std::endl << std::endl;

	begin_time_vector = clock();
    for (ft::vector<int>::iterator it = m1_vector.begin(); it != m1_vector.end(); it++) {}
	ft_time_vector = float(clock () - begin_time_vector) /  CLOCKS_PER_SEC;
	std::cout << "temps ft = " << ft_time_vector << std::endl;

	begin_time_vector = clock();
    for (std::vector<int>::iterator it = m2_vector.begin(); it != m2_vector.end(); it++) {}
	std_time_vector = float(clock () - begin_time_vector) /  CLOCKS_PER_SEC;
	std::cout << "temps std = " << std_time_vector << std::endl;

	std::cout << "ft est " << ft_time_vector / std_time_vector << "x plus lent que le vrai container" << std::endl;

	std::cout << " ------------------------ MAP BIG INSERT ------------------------ " << std::endl << std::endl;

	ft::map<int, int> m1;
    unsigned int i = 0;
	clock_t begin_time = clock();
    while ( i < 10000 ){
        m1.insert(ft::pair<int, int>(i, i));
        i++;
    }
	float ft_time = float(clock () - begin_time) /  CLOCKS_PER_SEC;
	std::cout << "temps ft = " << ft_time << std::endl;

	std::map<int, int> m2;
    i = 0;
	begin_time = clock();
    while ( i < 10000 ){
        m2.insert(std::pair<int, int>(i, i));
        i++;
    }
	float std_time = float(clock () - begin_time) /  CLOCKS_PER_SEC;
	std::cout << "temps std = " << std_time << std::endl;

	std::cout << "ft est " << ft_time / std_time << "x plus lent que le vrai container" << std::endl;

	std::cout << " ------------------------ MAP BIG ITERATOR ------------------------ " << std::endl << std::endl;

	begin_time = clock();
	for (ft::map<int, int>::reverse_iterator it = m1.rbegin(); it != m1.rend(); ++it) {}
	ft_time = float(clock () - begin_time) /  CLOCKS_PER_SEC;
	std::cout << "temps ft it = " << ft_time << std::endl;

	begin_time = clock();
	for (std::map<int, int>::reverse_iterator it = m2.rbegin(); it != m2.rend(); ++it) {}
	std_time = float(clock () - begin_time) /  CLOCKS_PER_SEC;
	std::cout << "temps std it = " << std_time << std::endl;

	std::cout << "ft it est " << ft_time / std_time << "x plus lent que le vrai container" << std::endl;

	std::cout << " ------------------------ SET BIG INSERT ------------------------ " << std::endl << std::endl;

	ft::set<int> m1_set;
    i = 0;
	begin_time = clock();
    while ( i < 10000 ){
        m1_set.insert(i);
        i++;
    }
	ft_time = float(clock () - begin_time) /  CLOCKS_PER_SEC;
	std::cout << "temps ft = " << ft_time << std::endl;

	std::set<int> m2_set;
    i = 0;
	begin_time = clock();
    while ( i < 10000 ){
        m2_set.insert(i);
        i++;
    }
	std_time = float(clock () - begin_time) /  CLOCKS_PER_SEC;
	std::cout << "temps std = " << std_time << std::endl;

	std::cout << "ft est " << ft_time / std_time << "x plus lent que le vrai container" << std::endl;

	std::cout << " ------------------------ SET BIG ITERATOR ------------------------ " << std::endl << std::endl;

	begin_time = clock();
	for (ft::set<int>::reverse_iterator it = m1_set.rbegin(); it != m1_set.rend(); ++it) {}
	ft_time = float(clock () - begin_time) /  CLOCKS_PER_SEC;
	std::cout << "temps ft it = " << ft_time << std::endl;

	begin_time = clock();
	for (std::set<int>::reverse_iterator it = m2_set.rbegin(); it != m2_set.rend(); ++it) {}
	std_time = float(clock () - begin_time) /  CLOCKS_PER_SEC;
	std::cout << "temps std it = " << std_time << std::endl;

	std::cout << "ft it est " << ft_time / std_time << "x plus lent que le vrai container" << std::endl;

	std::cout << " ------------------------ SET TEST ORDERED ------------------------ " << std::endl << std::endl;

	ft::set<std::string> ft_set_or;

	ft_set_or.insert(std::string("10"));
	ft_set_or.insert(std::string("2"));
	ft_set_or.insert(std::string("300"));

	for (ft::set<std::string>::reverse_iterator it = ft_set_or.rbegin(); it != ft_set_or.rend(); ++it)
		std::cout << "ft set = " << *it << std::endl;

	std::cout << std::endl;

	std::set<std::string> std_set_or;

	std_set_or.insert(std::string("10"));
	std_set_or.insert(std::string("2"));
	std_set_or.insert(std::string("300"));

	for (std::set<std::string>::reverse_iterator it = std_set_or.rbegin(); it != std_set_or.rend(); ++it)
		std::cout << "std set = " << *it << std::endl;

	return 0;
}