#ifndef FILESCANNER_HPP
#define FILESCANNER_HPP

#include <string>
#include <pthread.h>
#include "SafeQueue.hpp"

extern pthread_t main_producer_thread_id;

struct ScanArgs {
    SafeQueue* safequeue;
    std::string path;
};

class FileScanner {
public:
    static void* parseDirectory(void* args);
};

#endif
