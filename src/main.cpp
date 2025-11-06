#include <iostream>
#include <string>
#include "FileScanner.hpp"
#include "WorkerManager.hpp"
#include <pthread.h>
#include "SafeQueue.hpp"


pthread_t main_producer_thread_id;


int main(int argc, char** argv){

    if(argc!=3){
        std::cerr<<"Allowed usage: "<<argv[0]<<" <directory> <keyword>"<<std::endl;
        return 1;
    }

    std::string directory= argv[1];
    std::string keyword= argv[2];

    const int numOfWorkers= 10;

    
    SafeQueue safequeue ;

    main_producer_thread_id= pthread_self();
        
    ScanArgs args{&safequeue, directory};
    pthread_t fileScanner;
    pthread_create(&fileScanner, nullptr, FileScanner::parseDirectory, &args);
    WorkerManager manager(&safequeue, keyword, numOfWorkers);
    manager.spawnThreads();
    
    pthread_join(fileScanner, nullptr);
    safequeue.setDone();
    manager.joinThreads();

    return 0;
}