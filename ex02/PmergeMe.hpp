#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>


class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	static float run(std::vector<int>& container);
	static float run(std::deque<int>& container);

private:

};

#endif // PMERGEME_HPP