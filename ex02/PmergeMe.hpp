#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>
#include <cstddef>

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
        static int generateJacobsthal(const int num);


        static void sort(std::vector<int>& winners, std::vector<int>& losers);
        static void sort(std::deque<int>& winners, std::deque<int>& losers);
        static void createPairs(std::vector<int>& winners, std::vector<int>& losers);
        static void createPairs(std::deque<int>& container, std::deque<int>& winners,
                                          std::deque<int>& losers);
        static void insertRange(std::size_t firstToInsert, std::size_t lastToInsert, std::deque<int>& winners,
                                std::deque<int>& sortedLosers, const std::deque<int> origWinners);
};

#endif // PMERGEME_HPP