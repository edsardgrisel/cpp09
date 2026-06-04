#include "PmergeMe.hpp"
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>

static void printVector(std::vector<int> container)
{
    for(int num : container)
        std::cout << num <<  " ";
    std::cout << std::endl;
}

int main(int argc, char const* argv[])
{
    if (argc == 1)
    {
        std::cout << "Provide the numbers as individual arguments" << std::endl;
        return 1;
    }
    std::vector<int> vector;
    std::deque<int>  deque;
    for (int i = 1; i < argc; i++)
    {
        int num;
        try
        {
            num = std::stoi(argv[i]);
        }
        catch (std::exception& e)
        {
            std::cerr << "Failed to convert argument to int. " << e.what() << std::endl;
            return 1;
        }
        if (num <= 0)
        {
            std::cerr << "Provide positive numbers only." << std::endl;
            return 1;
        }
        vector.push_back(num);
        deque.push_back(num);
    }
    std::vector<int> vectorStdSort = vector;
    std::deque<int> dequeStdSort = deque;

    std::cout << "Before: ";
    printVector(vector);

    float vectorTime = PmergeMe::run(vector);
    if (vectorTime < 0)
    {
        std::cerr << "Sorting vector failed. Shutting down" << std::endl;
        return 1;
    }
    float dequeTime = PmergeMe::run(deque);
    if (dequeTime < 0)
    {
        std::cerr << "Sorting vector failed. Shutting down" << std::endl;
        return 1;
    }
    
    std::sort(vectorStdSort.begin(), vectorStdSort.end());
    std::sort(dequeStdSort.begin(), dequeStdSort.end());

    if (vector == vectorStdSort)
        std::cout << "Vector sort: OK\n";
    else
        std::cout << "Vector sort: FAILED\n";
    
    if (std::vector<int>(deque.begin(), deque.end()) == std::vector<int>(dequeStdSort.begin(), dequeStdSort.end()))
        std::cout << "Deque sort: OK\n";
    else
        std::cout << "Deque sort: FAILED\n";

    std::cout << "After: ";
    printVector(vector);
    return 0;
}
