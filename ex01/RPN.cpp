#include "RPN.hpp"

#include <string>
#include <stack>
#include <iostream>
////////////////////////
// Public              /
////////////////////////

RPN::RPN() {}

RPN::RPN(const RPN& other) 
{
	(void) other;
}
RPN& RPN::operator=(const RPN& other) 
{
	(void) other;
	return *this;
}
RPN::~RPN() {}

void RPN::execute(const std::string exprStr) 
{
	std::stack<float> stack;
	if (!isValidInput(exprStr))
	{
		std::cerr << "Error: input not in space separated number/operator format" << std::endl;
		return;
	}

	for (char c : exprStr)
	{
		if (c == ' ')
			continue;

		if (isdigit(c))
			stack.push(c - '0');
		else if (isOperator(c))
		{
			if (stack.size() < 2)
			{
				std::cerr << "Error: cannot perform operation with less than 2 numbers on the stack" << std::endl;
				return;
			}

			float right = stack.top();
			stack.pop();
			float left = stack.top();
			stack.pop();

			if (c == '+')
				stack.push(left + right);
			if (c == '-')
				stack.push(left - right);
			if (c == '*')
				stack.push(left * right);
			if (c == '/')
			{
				if (right == 0)
				{
					std::cerr << "Error: divide by zero not allowed" << std::endl;
					return;
				}
				stack.push(left / right);
			}
		}
	}
	if (stack.size() != 1)
	{
		std::cerr << "Error: still elements left on the stack" << std::endl;
		return;
	}
	std::cout << std::defaultfloat << stack.top() << std::endl;
}


////////////////////////
// Private             /
////////////////////////

bool RPN::isOperator(const char c)
{
	return ( c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isValidInput(const std::string exprStr)
{
	for (size_t i = 0; i < exprStr.size(); i++)
    {
        if (i % 2 == 0)
        {
            char c = exprStr[i];
            if (!(std::isdigit(static_cast<unsigned char>(c)) || isOperator(c)))
                return false;
        }
        else
        {
            if (exprStr[i] != ' ')
                return false;
        }
    }
	return true;
}
