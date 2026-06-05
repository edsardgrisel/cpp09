
#include "PmergeMe.hpp"

#include <chrono>
#include <deque>
#include <vector>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
    (void)other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void)other;
    return *this;
}

PmergeMe::~PmergeMe() {}

//////////
// vector
//////////

void PmergeMe::sort(std::vector<int>& container)
{
	(void)container;
}

float PmergeMe::run(std::vector<int>& container)
{
    (void)container;
    std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();

    sort(container);

    std::chrono::_V2::system_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds::rep             timeDifference =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return static_cast<float>(timeDifference);
}

//////////
// deque
//////////

void PmergeMe::sort(std::deque<int>& container)
{
	(void)container;
}

float PmergeMe::run(std::deque<int>& container)
{
    (void)container;

    std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();

    sort(container);

    std::chrono::_V2::system_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds::rep             timeDifference =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return static_cast<float>(timeDifference);
}