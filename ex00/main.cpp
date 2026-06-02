#include "BitcoinExchange.hpp"

#include <iostream>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		std::cout << "Provide an input file as the only argument" << std::endl;
		return 1;
	}

	BitcoinExchange exchange;
	if (exchange.init("data.csv") == false)
	{
		std::cout << "failed to init()" << std::endl;
		return 1;
	}
	if (exchange.execute(argv[1]) == false)
	{
		std::cout << "failed to execute()" << std::endl;
		return 1;
	}
	return 0;
}
