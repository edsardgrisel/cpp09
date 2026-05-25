#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <string>
#include <format> 


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
	std::ifstream in(inputFile);
	if (!in)
	{
		std::cout << "failed to open input file." << std::endl;
		return false;
	}

	bool visitedFirstLine = false;
	std::string line;
	while (std::getline(in, line))
	{
		std::istringstream lineStringStream(line);
		std::string left, right;
		if (std::getline(lineStringStream, left, '|') && std::getline(lineStringStream, right))
		{
			if (visitedFirstLine == false && left == "date" && right == "value")
			{
				visitedFirstLine = true;
				continue; // skip first line
			}
			// std::istringstream dateStringStream(left);
			// std::chrono::year_month_day ymd;
			// dateStringStream >> std::chrono::parse("%F", ymd); // %F = YYYY-MM-DD
			// if (!dateStringStream.fail() && ymd.ok())
			// {
			// 	// Valid date
			// }
			// else
			// {
				
			// }
			float value;
			try
			{
				value = std::stof(right);
			}
			catch(const std::exception& e)
			{
				std::cerr << "Failed to parse data.csv float: " << value << ". " << e.what() << std::endl;
				return false;
			}
		}
	}

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

	bool visitedFirstLine = false;
	std::string line;
	while (std::getline(in, line))
	{
		std::istringstream lineStringStream(line);
		std::string left, right;
		if (std::getline(lineStringStream, left, ',') && std::getline(lineStringStream, right))
		{
			if (visitedFirstLine == false && left == "date" && right == "exchange_rate")
			{
				visitedFirstLine = true;
				continue; // skip first line
			}
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