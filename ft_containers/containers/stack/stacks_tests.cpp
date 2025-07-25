#include "stack.hpp"
#include <stack>
#include <vector>
#include <deque>
#include "../vector/vector.hpp"

int stack_tests()
{
	std::cout << "----------------------------- TESTS STACK -----------------------------" << std::endl;

	std::cout << "----------------------------- CONSTRUCTOR -----------------------------" << std::endl;

	std::cout << "----------------------------- FT -----------------------------" << std::endl;

	ft::vector<int> ft_mydeque (3,100);          // deque with 3 elements
	ft::vector<int> ft_myvector (2,200);        // vector with 2 elements

	ft::stack<int> ft_first;                    // empty stack
	ft::stack<int> ft_second (ft_mydeque);         // stack initialized to copy of deque

	ft::stack<int,ft::vector<int> > ft_third;  // empty stack using vector
	ft::stack<int,ft::vector<int> > ft_fourth (ft_myvector);

	std::cout << "size of ft_first: " << ft_first.size() << '\n';
	std::cout << "size of ft_second: " << ft_second.size() << '\n';
	std::cout << "size of ft_third: " << ft_third.size() << '\n';
	std::cout << "size of ft_fourth: " << ft_fourth.size() << '\n';

	std::cout << "----------------------------- STD -----------------------------" << std::endl;

	std::deque<int> std_mydeque (3,100);          // deque with 3 elements
	std::vector<int> std_myvector (2,200);        // vector with 2 elements

	std::stack<int> std_first;                    // empty stack
	std::stack<int> std_second (std_mydeque);         // stack initialized to copy of deque

	std::stack<int,std::vector<int> > std_third;  // empty stack using vector
	std::stack<int,std::vector<int> > std_fourth (std_myvector);

	std::cout << "size of std_first: " << std_first.size() << '\n';
	std::cout << "size of std_second: " << std_second.size() << '\n';
	std::cout << "size of std_third: " << std_third.size() << '\n';
	std::cout << "size of std_fourth: " << std_fourth.size() << '\n';

	std::cout << "----------------------------- EMPTY -----------------------------" << std::endl;
	std::cout << "----------------------------- FT -----------------------------" << std::endl;

	ft::stack<int> ft_mystack2;
	int ft_sum (0);

	for (int i=1;i<=10;i++) ft_mystack2.push(i);

	while (!ft_mystack2.empty())
	{
		ft_sum += ft_mystack2.top();
		ft_mystack2.pop();
	}

	std::cout << "total: " << ft_sum << '\n';

	std::cout << "----------------------------- STD -----------------------------" << std::endl;

	std::stack<int> std_mystack2;
	int std_sum (0);

	for (int i=1;i<=10;i++) std_mystack2.push(i);

	while (!std_mystack2.empty())
	{
		std_sum += std_mystack2.top();
		std_mystack2.pop();
	}

	std::cout << "total: " << std_sum << '\n';

	std::cout << "----------------------------- SIZE -----------------------------" << std::endl;
	std::cout << "----------------------------- FT -----------------------------" << std::endl;

	ft::stack<int> ft_myints;
	std::cout << "0. size: " << ft_myints.size() << '\n';

	for (int i=0; i<5; i++) ft_myints.push(i);
	std::cout << "1. size: " << ft_myints.size() << '\n';

	ft_myints.pop();
	std::cout << "2. size: " << ft_myints.size() << '\n';

	std::cout << "----------------------------- STD -----------------------------" << std::endl;

	std::stack<int> std_myints;
	std::cout << "0. size: " << std_myints.size() << '\n';

	for (int i=0; i<5; i++) std_myints.push(i);
	std::cout << "1. size: " << std_myints.size() << '\n';

	std_myints.pop();
	std::cout << "2. size: " << std_myints.size() << '\n';

	std::cout << "----------------------------- TOP -----------------------------" << std::endl;
	std::cout << "----------------------------- FT -----------------------------" << std::endl;

	ft::stack<int> ft_mystack;

	ft_mystack.push(10);
	ft_mystack.push(20);

	ft_mystack.top() -= 5;

	std::cout << "ft_mystack.top() is now " << ft_mystack.top() << '\n';

	std::cout << "----------------------------- STD -----------------------------" << std::endl;

	std::stack<int> std_mystack;

	std_mystack.push(10);
	std_mystack.push(20);

	std_mystack.top() -= 5;

	std::cout << "std_mystack.top() is now " << std_mystack.top() << '\n';

	std::cout << "----------------------------- CONST TOP -----------------------------" << std::endl;
	std::cout << "----------------------------- FT -----------------------------" << std::endl;

	const ft::stack<int>::value_type ft_const_val = ft_mystack.top();

	std::cout << "ft_mystack.top() is now " << ft_const_val << '\n';

	std::cout << "----------------------------- STD -----------------------------" << std::endl;

	const std::stack<int>::value_type std_const_val = std_mystack.top();

	std::cout << "std_mystack.top() is now " << std_const_val << '\n';

	std::cout << "----------------------------- PUSH and POP -----------------------------" << std::endl;
	std::cout << "----------------------------- FT -----------------------------" << std::endl;

	ft::stack<int> ft_mystack3;

	for (int i=0; i<5; ++i) ft_mystack3.push(i);

	std::cout << "Popping out elements...";
	while (!ft_mystack3.empty())
	{
		std::cout << ' ' << ft_mystack3.top();
		ft_mystack3.pop();
	}
	std::cout << '\n';

	std::cout << "----------------------------- STD -----------------------------" << std::endl;

	std::stack<int> std_mystack3;

	for (int i=0; i<5; ++i) std_mystack3.push(i);

	std::cout << "Popping out elements...";
	while (!std_mystack3.empty())
	{
		std::cout << ' ' << std_mystack3.top();
		std_mystack3.pop();
	}
	std::cout << '\n';

	std::cout << "----------------------------- RELATIONAL OPERATOR -----------------------------" << std::endl;
	std::cout << "----------------------------- FT -----------------------------" << std::endl;

	if (ft_mystack2 == ft_mystack2)
		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (ft_mystack2 != ft_mystack2)
		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (ft_mystack2 < ft_mystack2)

		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (ft_mystack2 <= ft_mystack2)
		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (ft_mystack2 > ft_mystack2)
		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (ft_mystack2 >= ft_mystack2)

		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	std::cout << "----------------------------- STD -----------------------------" << std::endl;

	if (std_mystack2 == std_mystack2)
		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (std_mystack2 != std_mystack2)
		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (std_mystack2 < std_mystack2)

		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (std_mystack2 <= std_mystack2)
		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (std_mystack2 > std_mystack2)
		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	if (std_mystack2 >= std_mystack2)

		std::cout << "PAREIL" << std::endl;
	else
		std::cout << "PAS PAREIL" << std::endl;

	return 0;
}

int main()
{
	stack_tests();
	return 0;
}