#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>


////////////////////////
// Public              /
////////////////////////

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    this->db_ = other.db_;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
	{
        this->db_ = other.db_;
    }
    return *this;
}


BitcoinExchange::~BitcoinExchange() {}



bool BitcoinExchange::init(const std::string dbFilePath)
{
	if (setDb(dbFilePath) == false)
		return false;
	return true;
}


bool BitcoinExchange::execute(std::string inputFile)
{
	for (auto& [l, r] : this->db_)
		std::cout << l << "," << r << std::endl;
	(void) inputFile;
	return true;	
}


////////////////////////
// Private             /
////////////////////////

bool BitcoinExchange::setDb(const std::string dbFilePath)
{
	std::ifstream in(dbFilePath);
	if (!in)
	{
		std::cout << "failed to open db file. Download the file from the subject and put it in the ex00 folder" << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(in, line))
	{
		std::istringstream lineStrinStream(line);
		std::string left, right;
		if (std::getline(lineStrinStream, left, ',') && std::getline(lineStrinStream, right))
		{
			if (left == "date" && right == "exchange_rate")
				continue;
			float price;
			try
			{
				price = std::stof(right);
			}
			catch(const std::exception& e)
			{
				std::cerr << "Failed to parse data.csv float: " << price << ". " << e.what() << std::endl;
				return false;
			}
			this->db_[left] = price;
		}
	}
	return true;
}