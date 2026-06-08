#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <cstddef>
#include <vector>

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        template <typename Container>
        static float run(Container& container);

    private:
        static int generateJacobsthal(const int num);

        template <typename Container>
        static void sort(Container& winners, Container& losers);

        template <typename Container>
        static void createPairs(Container& container, Container& winners, Container& losers);

        template <typename Container>
        static void insertRange(std::size_t firstToInsert, std::size_t lastToInsert,
                                Container& winners, Container& sortedLosers,
                                const Container& origWinners);
};

extern template float PmergeMe::run<std::vector<int>>(std::vector<int>& container);
extern template float PmergeMe::run<std::deque<int>>(std::deque<int>& container);

#endif // PMERGEME_HPP