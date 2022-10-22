#include "stack.hpp"
#include <iostream>
#include <stack>

int main()
{
	ft::stack<int> std_s;
	ft::stack<int> std_scopy;

	if (std_s.empty())
		std::cout << "Stack is empty\n";

	for (int i = 1; i < 5; i++)
		std_s.push(i*10);
	std_scopy = std_s;
	std::cout << "Stack has "<< std_s.size() << " elements\n";
	while (!std_s.empty())
	{
		std::cout << std_s.top() << std::endl;
		std_s.pop();
	}

	std::cout << "Stack has "<< std_s.size() << " elements\n";
	if (std_s == std_scopy)
		std::cout << "Stacks are equal\n";
	else
		std::cout << "Stacks are not equal\n";


}