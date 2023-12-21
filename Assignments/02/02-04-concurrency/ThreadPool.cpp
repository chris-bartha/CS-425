//
// Created by chrisxo on 12/20/23.
//

#include "ThreadPool.h"
//
// Created by chrisxo on 12/20/23.
//

#ifndef THREADPOOL_CPP
#define THREADPOOL_CPP

ThreadPool::ThreadPool(std::size_t numThreads) {
    for (std::size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back([this] { threadFunc(); });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }

    condition.notify_all();

    for (auto& thread : threads) {
        thread.join();
    }
}

template <class F, class... Args>
void ThreadPool::enqueue(F&& f, Args&&... args) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.emplace(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    }

    condition.notify_one();
}

void ThreadPool::threadFunc() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty()) {
                return;
            }

            task = std::move(tasks.front());
            tasks.pop();
        }

        task();
    }
}

void ThreadPool::ProcessRange(const LychrelData& data, std::size_t start, std::size_t end, Records& records, std::size_t& maxIter) {
    for (size_t i = start; i < end; ++i) {
        Number number = data[i];
        size_t iter = 0;

        Number n = number;

        // The Lychrel loop - for any iteration, take the number, reverse
        //   its digits, and sum those values together.  If that sum
        //   is a palindrome, stop processing
        while (!n.is_palindrome() && ++iter < MaxIterations) {

            Number sum(n.size());   // Value used to store current sum of digits
            Number r = n.reverse(); // reverse the digits of the value

            // An iterator pointing to the first digit of the reversed
            //   value.  This iterator will be incremented to basically
            //   traverse the digits of the main number in reverse
            auto rd = n.begin();
            bool carry = false;  // flag to indicate if we had a carry

            // Sum the digits using the "transform" algorithm.  This
            //   algorithm traverses a range of values (in our case,
            //   starting with the least-siginificant [i.e., right most]
            //   digit) of the original number, adding each digit to its
            //   matching digit (by position) in the reversed number.
            //
            // The result is stored in the sum variable, which is
            //   built up one digit at a time, respecting if a carry
            //   digit was necessary for any iteration.
            std::transform(n.rbegin(), n.rend(), sum.rbegin(),
                           [&](auto d) {
                               auto v = d + *rd++ + carry;
                               carry = v > 9;
                               if (carry) { v -= 10; }
                               return v;
                           });

            // If there's a final carry value, prepend that to the sum
            if (carry) { sum.push_front(1); }

            // Transfer the sum making it the next number to be processed
            //   (i.e., reversed, summed, and checked if it's a
            //   palindrome)
            n = sum;
        }

        // Update records within the critical section
        {
            std::lock_guard<std::mutex> lock(mutex);

            // Update our records.  First, determine if we have a new
            //   maximum number of iterations that isn't the control limit
            //   (MaxIterations) for a particular number.  If we're less
            //   tha the current maximum (maxIter) or we've exceeded the number
            //   of permissible iterations, ignore the current result and move
            //   onto the next number.
            if (iter < maxIter || iter == MaxIterations) { continue; }

            // Otherwise update our records, which possibly means discarding
            //   our current maximum and rebuilding our records list.
            Record record{number, n};

            if (iter > maxIter) {
                records.clear();
                maxIter = iter;
            }
            records.push_back(record);
        }
    }
}



#endif //THREADPOOL_CPP
