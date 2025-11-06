#ifndef WORKERMANAGER_HPP
#define WORKERMANAGER_HPP

#include "FileSearcher.hpp"
#include "SafeQueue.hpp"
#include <pthread.h>
#include <vector>
#include <string>

class WorkerManager {
    SafeQueue *safequeue;
    std::string keyword;
    int numOfWorkers;
    std::vector<pthread_t> threads;
    pthread_mutex_t mutex_log;

    static void* Worker(void* arg);
    void workerRoutine();

public:
    WorkerManager(SafeQueue* q, std::string keyword, const int &numOfWorkers);
    void spawnThreads();
    void joinThreads();
    ~WorkerManager();
};

#endif
