//
// Created by chrisxo on 12/20/23.
//

#include "Thready.h"
//
// Created by chrisxo on 12/20/23.
//

#ifndef INC_02_THREADY_H
#define INC_02_THREADY_H

std::mutex Thready::mutex;

void Thready::ProcessRange(const LychrelData& data, size_t start, size_t end, Records& records, size_t& maxIter) {
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
                           }
            );

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


#endif //INC_02_THREADY_H
