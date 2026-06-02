#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		bool init(const std::string dbFilePath);
		bool execute(const std::string inputFile);

	private:
		std::map<std::string, float> db_;

		bool setDb(const std::string dbFilePath);
		bool isLeapYear(const int year);
		bool isValidDateFormat(const std::string dateStr);
		bool isValidDate(const std::string dateStr);
};

#endif // BITCOINEXCHANGE_HPP