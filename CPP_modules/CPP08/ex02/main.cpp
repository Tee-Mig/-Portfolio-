#include "MutantStack.hpp"
#include <list>
#include <vector>
int main()
{
	std::cout << std::endl << "------------------------------ MutantStack ------------------------------" << std::endl;

	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--it;

	while (it != ite)
	{
	std::cout << *it << std::endl;
	++it;
	}
	std::stack<int> s(mstack);

	std::cout << std::endl << "------------------------------ Vector ------------------------------" << std::endl;

	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(17);
	std::cout << vec.back() << std::endl;
	vec.pop_back();
	std::cout << vec.size() << std::endl;
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(737);
	//[...]
	vec.push_back(0);
	std::vector<int>::iterator it2 = vec.begin();
	std::vector<int>::iterator it2_end = vec.end();

	++it2;
	--it2;

	while (it2 != it2_end)
	{
	std::cout << *it2 << std::endl;
	++it2;
	}

	std::cout << std::endl << "------------------------------ List ------------------------------" << std::endl;

	std::vector<int> lst;
	lst.push_back(5);
	lst.push_back(17);
	std::cout << lst.back() << std::endl;
	lst.pop_back();
	std::cout << lst.size() << std::endl;
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	//[...]
	lst.push_back(0);
	std::vector<int>::iterator it3 = lst.begin();
	std::vector<int>::iterator it3_end = lst.end();

	++it3;
	--it3;

	while (it3 != it3_end)
	{
	std::cout << *it3 << std::endl;
	++it3;
	}

	return 0;
}