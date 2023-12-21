//
// Created by chrisxo on 12/20/23.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <mutex>
#include <queue>
#include <thread>
#include <functional>
#include <condition_variable>

#include "LychrelData.h"
#include "Types.h"
#include "Constants.h"

class ThreadPool {
public:
    ThreadPool(std::size_t numThreads);
    ~ThreadPool();

    template <class F, class... Args>
    void enqueue(F&& f, Args&&... args);

    void ProcessRange(const LychrelData& data, std::size_t start, std::size_t end, Records& records, std::size_t& maxIter);

private:
    void threadFunc();

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop = false;

    std::mutex mutex; // Mutex for synchronization when updating shared variables
};

#endif //THREADPOOL_H
