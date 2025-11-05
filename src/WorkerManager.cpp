#include "WorkerManager.hpp"
#include <iostream>

WorkerManager::WorkerManager(SafeQueue* q, std::string keyword, const int &numOfWorkers) {
    safequeue = q;
    this->keyword = keyword;
    this->numOfWorkers = numOfWorkers;
    threads.resize(numOfWorkers);
    pthread_mutex_init(&mutex_log, nullptr);
}

void* WorkerManager::Worker(void* arg) {
    auto* self = static_cast<WorkerManager*>(arg);
    self->workerRoutine();
    return nullptr;
}

void WorkerManager::workerRoutine() {
    std::string filePath;
    while ((filePath = safequeue->pop()) != "") {
        if (FileSearcher::containsKeyword(filePath, keyword)) {
            pthread_mutex_lock(&mutex_log);
            std::cout << filePath << " contains " << keyword << std::endl;
            pthread_mutex_unlock(&mutex_log);
        }
    }
}

void WorkerManager::spawnThreads() {
    for (int i = 0; i < numOfWorkers; i++) {
        pthread_create(&threads[i], nullptr, Worker, this);
    }
}

void WorkerManager::joinThreads() {
    for (auto &thread : threads) {
        pthread_join(thread, nullptr);
    }
}

WorkerManager::~WorkerManager() {
    pthread_mutex_destroy(&mutex_log);
}
