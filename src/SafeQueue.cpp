#include "SafeQueue.hpp"

SafeQueue::SafeQueue() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond_pop, nullptr);
}

void SafeQueue::push(const std::string &path) {
    pthread_mutex_lock(&mutex);
    q.push(path);
    pthread_cond_signal(&cond_pop);
    pthread_mutex_unlock(&mutex);
}

std::string SafeQueue::pop() {
    pthread_mutex_lock(&mutex);
    while (q.empty() && !done) {
        pthread_cond_wait(&cond_pop, &mutex);
    }

    if (q.empty() && done) {
        pthread_mutex_unlock(&mutex);
        return "";
    }

    std::string res = q.front();
    q.pop();

    pthread_mutex_unlock(&mutex);
    return res;
}

void SafeQueue::setDone() {
    pthread_mutex_lock(&mutex);
    done = true;
    pthread_cond_broadcast(&cond_pop);
    pthread_mutex_unlock(&mutex);
}

SafeQueue::~SafeQueue() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_pop);
}
