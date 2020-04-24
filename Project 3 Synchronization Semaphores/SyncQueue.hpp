#pragma once

#include <string>
#include <list>
#include <semaphore.h>

class SyncQueue {
public:
    struct message{
        int queueID;
        std::string producerID;
        std::string messageID;

        message(int _queueID, std::string _producerID, std::string _messageID);

        friend std::ostream& operator<<(std::ostream& os, const message& m);
    };

    SyncQueue(size_t queueSize, int queueID);
    ~SyncQueue();
    void produce(message m);
    void consume(bool randomChoice, size_t index);
    const void read();

private:
    std::list<message> queue;
    int queueID;
    int readersCounter = 0;
    
    sem_t full;
    sem_t empty;
    sem_t mutexEntry;
    sem_t mutexCounter;
};