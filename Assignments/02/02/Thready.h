//
// Created by chrisxo on 12/20/23.
//

#ifndef THREADY_H
#define THREADY_H

#include <mutex>

#include "LychrelData.h"
#include "Types.h"
#include "Constants.h"

class Thready {
public:
    static void ProcessRange(const LychrelData& data, size_t start, size_t end, Records& records, size_t& maxIter);
private:
    // Mutex for synchronization when updating shared variables
    static std::mutex mutex; // Static mutex
};


#endif //THREADY_H
