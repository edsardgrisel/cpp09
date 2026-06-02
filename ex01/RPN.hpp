#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN
{
public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	void execute(const std::string exprStr);

private:
	bool isOperator(const char c);
	bool isValidInput(const std::string exprStr);
};

#endif // RPN_HPP