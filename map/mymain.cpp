#include "map.hpp"
#include <iostream>

int main()
{
	ft::map<int, int> m;
	ft::map<int, int> m_copy;

	m.insert({1,1});
	m.insert(ft::make_pair(2,2));
	m.insert(ft::make_pair(3,3));
	m.insert(ft::make_pair(4,4));
	m.insert(ft::make_pair(5,5));
	m.insert(ft::make_pair(6,6));
	m.insert({7,7});
	m_copy = m;

	std::cout << "\033[32m [iterator test] \033[0m" << std::endl;
	ft::map<int, int>::iterator it;
	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl; 

	std::cout << std::endl;
 
	std::cout << "\033[32m [reverse iterator test] \033[0m" << std::endl;
	ft::map<int, int>::reverse_iterator rit;
	for (rit = m.rbegin(); rit != m.rend(); ++rit)
		std::cout << rit->first << " " << rit->second << std::endl;
		
	std::cout << "\033[32m [relational operators test] \033[0m" << std::endl;
	if (m_copy == m)
		std::cout << "Maps are equal\n";
	else
		std::cout << "Maps are not equal\n";

	std::cout << "\033[32m [member functions test] \033[0m" << std::endl;
	if ( (it = m.find(5)) != m.end())
		std::cout << "Found key: " << it->first << " with value: " << it->second << std::endl; 
	
	m.erase(it);
	std::cout << "Map has " << m.size() << " elements:\n";
	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
	
	m.insert(m.begin(), {10, 10});
	std::cout << "Map has " << m.size() << " elements:\n";
	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;

	ft::map<int, int> m_copy2;
	m_copy2.insert(m.find(3), m.find(10));
	std::cout << "m_copy2 has " << m_copy2.size() << " elements:\n";
	for (it = m_copy2.begin(); it != m_copy2.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
	
	m_copy2.erase(4);
	std::cout << "m_copy2 has " << m_copy2.size() << " elements:\n";
	for (it = m_copy2.begin(); it != m_copy2.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;

	m_copy2.erase(m_copy2.begin(), m_copy2.end());
	std::cout << "m_copy2 has " << m_copy2.size() << " elements:\n";
	for (it = m_copy2.begin(); it != m_copy2.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
	
	m_copy2.swap(m);
	std::cout << "m_copy2 has " << m_copy2.size() << " elements:\n";
	for (it = m_copy2.begin(); it != m_copy2.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
	std::cout << "Map has " << m.size() << " elements:\n";
	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
	if (m.empty())
		std::cout << "Map is empty.\n";
	return 0;
}