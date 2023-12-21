//
// Created by chrisxo on 12/20/23.
//

#ifndef TYPES_H
#define TYPES_H

// A structure recording the starting number, and its final palindrome.
//   An vector of these records (typedefed to "Records") is built during
//   program execution, and output before the program terminates.
struct Record {
    Number n;
    Number palindrome;
};
using Records = std::vector<Record>;

#endif //TYPES_H
