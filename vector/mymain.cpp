#include "vector.hpp"
#include <vector>
#include <iostream>

int main()
{
	ft::vector<int> ft_v;

	for (int i = 1; i < 5; i++)
		ft_v.push_back(i * 10);
	
	ft::vector<int> ft_vcopy;
	ft_vcopy = ft_v;
	ft::vector<int> ft_vcopy2 = ft_v;

	std::cout << "\033[32m [iterator test] \033[0m" << std::endl;
	ft::vector<int>::iterator ft_it;
	std::cout << "ft_v has " << ft_v.size() << " elements:\n";
	for (ft_it = ft_v.begin(); ft_it != ft_v.end(); ft_it++)
		std::cout << *ft_it << std::endl;
	std::cout << "ft_vcopy has " << ft_vcopy2.size() << " elements:\n";
	for (ft_it = ft_vcopy.begin(); ft_it != ft_vcopy.end(); ft_it++)
		std::cout << *ft_it << std::endl;
	std::cout << "ft_vcopy2 has " << ft_vcopy2.size() << " elements:\n";
	for (ft_it = ft_vcopy2.begin(); ft_it != ft_vcopy2.end(); ft_it++)
		std::cout << *ft_it << std::endl;

	std::cout << "\033[32m [reverse iterator test] \033[0m" << std::endl;
	ft::vector<int>::reverse_iterator ft_rit;
	std::cout << "ft_v has " << ft_v.size() << " elements:\n";
	for (ft_rit = ft_v.rbegin(); ft_rit != ft_v.rend(); ft_rit++)
		std::cout << *ft_rit << std::endl;
	std::cout << "ft_vcopy has " << ft_vcopy2.size() << " elements:\n";
	for (ft_rit = ft_vcopy.rbegin(); ft_rit != ft_vcopy.rend(); ft_rit++)
		std::cout << *ft_rit << std::endl;
	std::cout << "ft_vcopy2 has " << ft_vcopy2.size() << " elements:\n";
	for (ft_rit = ft_vcopy2.rbegin(); ft_rit != ft_vcopy2.rend(); ft_rit++)
		std::cout << *ft_rit << std::endl;


	std::cout << "\033[32m [relational operators test] \033[0m" << std::endl;
	if (ft_v == ft_vcopy)
		std::cout << "Vectors are equal\n";
	else
		std::cout << "Vectors are not equal\n";
	
	std::cout << "\033[32m [Member functions test] \033[0m" << std::endl;
	ft_v.pop_back();
	ft_v.pop_back();
	std::cout << "ft_v has " << ft_v.size() << " elements:\n";
	for (ft_it = ft_v.begin(); ft_it != ft_v.end(); ft_it++)
		std::cout << *ft_it << std::endl;

	ft_v.resize(10);
	ft_v.assign(10, 5); 
	std::cout << "ft_v has " << ft_v.size() << " elements:\n";
	for (ft_it = ft_v.begin(); ft_it != ft_v.end(); ft_it++)
		std::cout << *ft_it << std::endl;

	ft_v.insert(ft_v.begin(), 6);
	ft_v.insert(ft_v.begin() + 1, 3, 7);
	std::cout << "ft_v has " << ft_v.size() << " elements:\n";
	for (ft_it = ft_v.begin(); ft_it != ft_v.end(); ft_it++)
		std::cout << *ft_it << std::endl;

	ft_v.erase(ft_v.begin());
	std::cout << "ft_v has " << ft_v.size() << " elements:\n";
	for (ft_it = ft_v.begin(); ft_it != ft_v.end(); ft_it++)
		std::cout << *ft_it << std::endl;
	ft_v.erase(ft_v.begin(), ft_v.end());
	std::cout << "ft_v has " << ft_v.size() << " elements:\n";
	for (ft_it = ft_v.begin(); ft_it != ft_v.end(); ft_it++)
		std::cout << *ft_it << std::endl;

	if (ft_v.empty())
		std::cout << "Vector is empty.\n";

	ft_v.swap(ft_vcopy);
	std::cout << "ft_v has " << ft_v.size() << " elements:\n";
	for (ft_it = ft_v.begin(); ft_it != ft_v.end(); ft_it++)
		std::cout << *ft_it << std::endl;
	std::cout << "ft_vcopy has " << ft_vcopy.size() << " elements:\n";
	for (ft_it = ft_vcopy.begin(); ft_it != ft_vcopy.end(); ft_it++)
		std::cout << *ft_it << std::endl;
	
	return 0;
}