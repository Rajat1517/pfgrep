#include "FileSearcher.cpp"
#include "SafeQueue.cpp"
#include <pthread.h> // C API
#include <iostream>
#include <vector>


class WorkerManager{

    SafeQueue *safequeue;
    std::string keyword;
    int numOfWorkers;
    std::vector<pthread_t> threads;
    pthread_mutex_t mutex_log;



    static void* Worker(void* arg){

        auto* self= static_cast<WorkerManager*>(arg);

        self->workerRoutine();

        return nullptr;

    }

    void workerRoutine(){
        std::string filePath;

        while( (filePath=safequeue->pop())!= ""){
            if(FileSearcher::containsKeyword(filePath,keyword)){
                pthread_mutex_lock(&mutex_log);
                std::cout<<filePath<<" contains "<< keyword<<std::endl;
                pthread_mutex_unlock(&mutex_log);
            }
        }
    }

    public:

    WorkerManager(SafeQueue* q,std::string keyword, int numOfWorkers){
        safequeue=q;
        this->keyword= keyword;
        this->numOfWorkers= numOfWorkers;
        threads.resize(numOfWorkers);
        pthread_mutex_init(&mutex_log, nullptr);
    }


    void spawnThreads(){

        for(int i=0;i<numOfWorkers;i++){
            pthread_create(&threads[i],nullptr, Worker, this);
        }

        for(auto &thread: threads){
            pthread_join(thread,nullptr);
        }
    }

    ~WorkerManager(){
        pthread_mutex_destroy(&mutex_log);
    }

};