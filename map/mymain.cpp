#include "map.hpp"
#include <iostream>

int main()
{
	ft::map<int, int> m;
	m.insert({1,1});
	m.insert(ft::make_pair(2,2));
	m.insert(ft::make_pair(3,3));
	m.insert(ft::make_pair(4,4));
	m.insert(ft::make_pair(5,5));
	m.insert(ft::make_pair(6,6));
	m.insert({7,7});
	ft::map<int, int>::reverse_iterator ri;
	for (ri = m.rbegin(); ri != m.rend(); ++ri)
		std::cout << ri->first << " " << ri->second << std::endl;
		
	std::cout << std::endl; 

	ft::map<int, int>::iterator i;
	for (i = m.begin(); i != m.end(); ++i)
		std::cout << i->first << " " << i->second << std::endl; 


	return 0;
}