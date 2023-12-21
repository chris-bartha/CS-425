/////////////////////////////////////////////////////////////////////////////
//
//  lychrel.cpp
//
//  A program that searches for the largest (in terms of number of
//    iterations without exceeding a specified maximum) palindrome value.
//
//  The program reports a list of numbers that share the maximum number of
//    iterations, along with the size and final palindrome number
//

// #include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <thread>

#include "LychrelData.h"
#include "Types.h"
#include "Constants.h"
#include "Thready.h"

//
// --- main ---
//
int main() {
    LychrelData data;
    Thready thready;

    std::cerr << "Processing " << data.size() << " values ...\n";

    size_t maxIter = 0;  // Records the current maximum number of iterations
    Records records; // list of values that took maxIter iterations

    // Calculate the number of elements each thread will process
    size_t numElementsPerThread = data.size() / MaxThreads;

    // Vector to hold thread objects
    std::vector<std::thread> threads;

    // Create and launch threads
    for (size_t i = 0; i < MaxThreads; ++i) {
        size_t start = i * numElementsPerThread;
        size_t end = (i == MaxThreads - 1) ? data.size() : (i + 1) * numElementsPerThread;

        threads.emplace_back(thready.ProcessRange, std::ref(data), start, end, std::ref(records), std::ref(maxIter));
    }

    // Join threads to wait for their completoin
    for (auto& thread : threads) {
        thread.join();
    }

    // Output our final results
    std::cout << "\nmaximum number of iterations = " << maxIter << "\n";
    for (auto& [number, palindrome] : records) {
        std::cout
                << "\t" << number
                << " : [" << palindrome.size() << "] "
                << palindrome << "\n";
    }

    return 0;
}