
#include "PmergeMe.hpp"

#include <chrono>
#include <cmath>
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

int PmergeMe::generateJacobsthal(const int n)
{
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;

    int previousJacobsthal = 0;
    int currentJacobsthal = 1;
    int nextJacobsthal = 0;

    for (int index = 2; index <= n; ++index)
    {
        nextJacobsthal = currentJacobsthal + 2 * previousJacobsthal;
        previousJacobsthal = currentJacobsthal;
        currentJacobsthal = nextJacobsthal;
    }
    return currentJacobsthal;
}

//////////
// vector
//////////

// void PmergeMe::createPairs(std::vector<int>& winners, std::vector<int>& losers){}

void PmergeMe::sort(std::vector<int>& winners, std::vector<int>& losers)
{
    (void)winners;
    (void)losers;
}

float PmergeMe::run(std::vector<int>& container)
{
    (void)container;
    std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();

    // sort(container);

    std::chrono::_V2::system_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds::rep             timeDifference =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return static_cast<float>(timeDifference);
}

//////////
// deque
//////////

void PmergeMe::createPairs(std::deque<int>& container, std::deque<int>& winners,
                           std::deque<int>& losers)
{
    std::deque<int> newWinners;
    std::deque<int> newLosers;

    size_t containerSize = container.size();
    size_t i = 0;
    for (; i + 1 < containerSize; i += 2)
    {
        int left = container[i];
        int right = container[i + 1];
        if (left > right)
        {
            newWinners.push_back(left);
            newLosers.push_back(right);
        }
        else
        {
            newWinners.push_back(right);
            newLosers.push_back(left);
        }
    }
    if (containerSize % 2 != 0)
        newLosers.push_back(container[i]);

    winners = std::move(newWinners);
    losers = std::move(newLosers);
}


void /*PmergeMe::*/insertRange(size_t firstToInsert, size_t lastToInsert, std::deque<int>& winners, std::deque<int>& losers, const std::deque<int> origWinners)
{
    if (firstToInsert > losers.size() - 1)
        firstToInsert = losers.size() - 1;
    
    if (lastToInsert > firstToInsert)
        return;

    for (size_t i = firstToInsert; i >= lastToInsert; i--)
    {
        size_t winnerIndex = 0;
        for (; winnerIndex < winners.size(); winnerIndex++)
        {
            if (winners[winnerIndex] == origWinners[i])
                break;
        }
        std::deque<int>::iterator currentWinnerIt = winners.begin() + winnerIndex;
        auto insertPos = std::lower_bound(winners.begin(), currentWinnerIt, losers[i]);
        winners.insert(insertPos, losers[i]);

    }
    
    
    
}

void PmergeMe::sort(std::deque<int>& winners, std::deque<int>& losers)
{
    if (winners.size() == 1)
        return;

    std::deque<int> newWinners;
    std::deque<int> newLosers;
    createPairs(winners, newWinners, newLosers);
    sort(newWinners, newLosers);
    std::deque<int> sortedLosers;

    for (int& newWinner : newWinners)
    {
        for (size_t i = 0; i < winners.size(); i++)
        {
            if (winners[i] == newWinner)
            {
                sortedLosers.push_back(losers[i]);
            }
        }
    }
    if (losers.size() != winners.size())
        sortedLosers.push_back(losers.back());

    const std::deque<int> constWinners = winners;


    int previousJacobsthal = -1;
    for (int index = 0; ; ++index)
    {
        int jacobsthal = generateJacobsthal(index);

        if (jacobsthal == previousJacobsthal)
            continue;


        insertRange(jacobsthal, generateJacobsthal(index - 1) + 1, winners, sortedLosers, constWinners);

        if (jacobsthal >= static_cast<int>(sortedLosers.size()))
            break;

        previousJacobsthal = jacobsthal;

    }
}

float PmergeMe::run(std::deque<int>& container)
{
    (void)container;

    std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();

    std::deque<int> winners;
    std::deque<int> losers;

    createPairs(container, winners, losers);
    sort(winners, losers);

    std::chrono::_V2::system_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds::rep             timeDifference =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return static_cast<float>(timeDifference);
}