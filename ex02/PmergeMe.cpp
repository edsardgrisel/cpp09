
#include "PmergeMe.hpp"

#include <algorithm>
#include <chrono>
#include <deque>
#include <utility>
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

template <typename Container> float PmergeMe::run(Container& container)
{
    const std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    Container winners;
    Container losers;

    createPairs(container, winners, losers);
    sort(winners, losers);

    container = winners;

    const std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    const std::chrono::microseconds::rep timeDifference = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return static_cast<float>(timeDifference);
}

template <typename Container>
void PmergeMe::createPairs(Container& container, Container& winners, Container& losers)
{
    Container newWinners;
    Container newLosers;

    std::size_t containerSize = container.size();
    std::size_t i = 0;
    for (; i + 1 < containerSize; i += 2)
    {
        typename Container::value_type left = container[i];
        typename Container::value_type right = container[i + 1];
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

template <typename Container>
void PmergeMe::insertRange(std::size_t firstToInsert, std::size_t lastToInsert, Container& winners,
                           Container& sortedLosers, const Container& origWinners)
{
    if (sortedLosers.empty())
        return;

    if (firstToInsert >= sortedLosers.size())
        firstToInsert = sortedLosers.size() - 1;

    if (lastToInsert > firstToInsert)
        return;

    for (int li = static_cast<int>(firstToInsert); li >= static_cast<int>(lastToInsert); --li)
    {
        if (static_cast<std::size_t>(li) < origWinners.size())
        {
            typename Container::value_type winnerValue = origWinners[li];
            typename Container::iterator   currentWinnerIt = std::find(winners.begin(), winners.end(), winnerValue);

            if (currentWinnerIt == winners.end())
                continue;

            typename Container::iterator insertPos = std::lower_bound(winners.begin(), currentWinnerIt, sortedLosers[li]);
            winners.insert(insertPos, sortedLosers[li]);
        }
        else
        {
            typename Container::iterator insertPos = std::lower_bound(winners.begin(), winners.end(), sortedLosers[li]);
            winners.insert(insertPos, sortedLosers[li]);
        }
    }
}

template <typename Container> void PmergeMe::sort(Container& winners, Container& losers)
{
    if (winners.size() <= 1)
    {
        Container origWinners = winners;
        if (!losers.empty())
            insertRange(losers.size() - 1, 0, winners, losers, origWinners);
        losers.clear();
        return;
    }

    Container newWinners;
    Container newLosers;
    createPairs(winners, newWinners, newLosers);
    sort(newWinners, newLosers);
    Container sortedLosers;

    for (typename Container::value_type newWinner : newWinners)
    {
        for (std::size_t i = 0; i < winners.size(); i++)
        {
            if (winners[i] == newWinner)
                sortedLosers.push_back(losers[i]);
        }
    }
    if (losers.size() != winners.size())
        sortedLosers.push_back(losers.back());

    const Container origWinners = newWinners;

    int previousJacobsthal = -1;
    for (int index = 0;; ++index)
    {
        int jacobsthal = generateJacobsthal(index);

        if (jacobsthal == previousJacobsthal)
            continue;

        if (jacobsthal >= static_cast<int>(sortedLosers.size()))
        {
            int last = static_cast<int>(sortedLosers.size()) - 1;
            if (last >= previousJacobsthal + 1)
                insertRange(static_cast<std::size_t>(last),
                            static_cast<std::size_t>(previousJacobsthal + 1), newWinners,
                            sortedLosers, origWinners);
            break;
        }

        if (jacobsthal >= previousJacobsthal + 1)
            insertRange(static_cast<std::size_t>(jacobsthal),
                        static_cast<std::size_t>(previousJacobsthal + 1), newWinners, sortedLosers,
                        origWinners);

        previousJacobsthal = jacobsthal;
    }

    winners = std::move(newWinners);
}

template float PmergeMe::run<std::vector<int>>(std::vector<int>& container);
template float PmergeMe::run<std::deque<int>>(std::deque<int>& container);