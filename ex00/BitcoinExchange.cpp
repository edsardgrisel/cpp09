#include "BitcoinExchange.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
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
    {

        return false;
    }
    return true;
}

bool BitcoinExchange::execute(std::string inputFile)
{
    std::ifstream in(inputFile);
    if (!in)
    {
        std::cout << "failed to open input file: " << inputFile << std::endl;
        return false;
    }

    bool        visitedFirstLine = false;
    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;
        std::string left, right;

        size_t pos = line.find(" | ");
        if (pos != std::string::npos)
        {
            left = line.substr(0, pos);
            right = line.substr(pos + 3);
        }

        if (visitedFirstLine == false)
        {
            visitedFirstLine = true;
            if (left == "date" && right == "value")
                continue; // skip first line
            else
            {
                std::cout << "Error: expected first line:'date | value' but got:'" << line << "'" << std::endl;
                return false;
            }
        }
        if (!isValidDate(left))
        {
            std::cout << "Error: bad date input => " << line << std::endl;
            continue;
        }
        float value;
        try
        {
            value = std::stof(right);
        }
        catch (...)
        {
            std::cout << "Error: bad value input => " << line << std::endl;
            continue;
        }
        if (value <= 0.0)
        {
            std::cout << "Error: not a positive number => " << line << std::endl;
            continue;
        }
        if (value >= 1000.0)
        {
            std::cout << "Error: too large a number => " << line << std::endl;
            continue;
        }

        // In execute() function, replace the db_ lookup:

        auto it = db_.lower_bound(left);
        if (it == db_.begin())
        {
            std::cout << "Error: date is earlier than all dates in the db" << std::endl;
            continue;
        }
        if (it != db_.end() && it->first != left)
            --it;
        else if (it == db_.end())
            --it;

        float result = it->second * value;

        std::cout << left + " => " + right + " = " << std::defaultfloat << result << std::endl;
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
        std::cout << "failed to open db file. Download the file from the subject and put it in the "
                     "ex00 folder"
                  << std::endl;
        return false;
    }

    bool        visitedFirstLine = false;
    std::string line;
    while (std::getline(in, line))
    {
        std::istringstream lineStringStream(line);
        std::string        left, right;
        if (std::getline(lineStringStream, left, ',') && std::getline(lineStringStream, right))
        {
            if (visitedFirstLine == false && left == "date" && right == "exchange_rate")
            {
                visitedFirstLine = true;
                continue; // skip first line
            }
            if (!isValidDate(left))
                return false;
            float price;
            try
            {
                price = std::stof(right);
            }
            catch (const std::exception& e)
            {
                std::cout << "Failed to parse data.csv float: " << price << ". " << e.what()
                          << std::endl;
                return false;
            }
            this->db_[left] = price;
        }
    }
    return true;
}

bool BitcoinExchange::isLeapYear(const int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 2009-01-02
bool BitcoinExchange::isValidDateFormat(const std::string dateStr)
{
    int len = dateStr.length();
    if (len != 10)
    {
        return false;
    }

    for (int i = 0; i < len; i++)
    {
        if (i == 4 || i == 7)
        {
            if (dateStr[i] != '-')
            {
                return false;
            }
        }
        else
        {
            if (!std::isdigit(static_cast<unsigned char>(dateStr[i])))
            {
                return false;
            }
        }
    }
    return true;
}

bool BitcoinExchange::isValidDate(const std::string dateStr)
{
    if (!isValidDateFormat(dateStr))
        return false;

    int year, month, day, monthLength;
    try
    {
        year = std::stoi(dateStr.substr(0, 4).c_str());
    }
    catch (...)
    {
        return false;
    }
    try
    {
        month = std::stoi(dateStr.substr(5, 2).c_str());
    }
    catch (...)
    {
        return false;
    }
    try
    {
        day = std::stoi(dateStr.substr(8, 2).c_str());
    }
    catch (...)
    {
        return false;
    }

    if (month < 1 || month > 12)
        return false;

    int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2)
        monthLength = isLeapYear(year) ? 29 : 28;
    else
        monthLength = daysInMonth[month];

    return day >= 1 && day <= monthLength;
}
