
#include "PmergeMe.hpp"

#include <algorithm>
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

void /*PmergeMe::*/ insertRange(size_t firstToInsert, size_t lastToInsert, std::deque<int>& winners,
                                std::deque<int>& sortedLosers, const std::deque<int> origWinners)
{
    if (sortedLosers.empty())
        return;

    if (firstToInsert >= sortedLosers.size())
        firstToInsert = sortedLosers.size() - 1;

    if (lastToInsert > firstToInsert)
        return;

    for (int li = static_cast<int>(firstToInsert); li >= static_cast<int>(lastToInsert); --li)
    {
        if (static_cast<size_t>(li) < origWinners.size())
        {
            int winnerValue = origWinners[li];
            std::deque<int>::iterator currentWinnerIt = std::find(winners.begin(), winners.end(), winnerValue);

            if (currentWinnerIt == winners.end())
                continue;

            std::deque<int>::iterator insertPos = std::lower_bound(winners.begin(), currentWinnerIt, sortedLosers[li]);
            winners.insert(insertPos, sortedLosers[li]);
        }
        else
        {
            // insert the unpaired loser if present
            auto insertPos = std::lower_bound(winners.begin(), winners.end(), sortedLosers[li]);
            winners.insert(insertPos, sortedLosers[li]);
        }
    }
}

void PmergeMe::sort(std::deque<int>& winners, std::deque<int>& losers)
{
    if (winners.size() <= 1)
    {
        std::deque<int> origWinners = winners;
        if (!losers.empty())
            insertRange(losers.size() - 1, 0, winners, losers, origWinners);
        losers.clear();
        return;
    }

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

    const std::deque<int> origWinners = newWinners;

    int previousJacobsthal = -1;
    for (int index = 0;; ++index)
    {
        int jacobsthal = generateJacobsthal(index);

        if (jacobsthal == previousJacobsthal)
            continue;

        // insert remaining losers beyond the last jacobsthal number that fits in the list length
        if (jacobsthal >= static_cast<int>(sortedLosers.size()))
        {
            int last = static_cast<int>(sortedLosers.size()) - 1;
            if (last >= previousJacobsthal + 1)
                insertRange(static_cast<size_t>(last), static_cast<size_t>(previousJacobsthal + 1),
                            newWinners, sortedLosers, origWinners);
            break;
        }

        // insert range [previousJacobsthal+1 .. jacobsthal] (right-to-left inside)
        if (jacobsthal >= previousJacobsthal + 1)
            insertRange(static_cast<size_t>(jacobsthal),
                        static_cast<size_t>(previousJacobsthal + 1), newWinners, sortedLosers,
                        origWinners);

        previousJacobsthal = jacobsthal;
    }

    winners = std::move(newWinners);
}

float PmergeMe::run(std::deque<int>& container)
{
    (void)container;

    std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();

    std::deque<int> winners;
    std::deque<int> losers;

    createPairs(container, winners, losers);
    sort(winners, losers);

    container = winners;

    std::chrono::_V2::system_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds::rep             timeDifference =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return static_cast<float>(timeDifference);
}