#ifndef SAFEQUEUE_HPP
#define SAFEQUEUE_HPP

#include <pthread.h>
#include <queue>
#include <string>

class SafeQueue {
    std::queue<std::string> q;
    pthread_mutex_t mutex;
    pthread_cond_t cond_pop;
    bool done = false;

public:
    SafeQueue();
    void push(const std::string &path);
    std::string pop();
    void setDone();
    ~SafeQueue();
};

#endif
