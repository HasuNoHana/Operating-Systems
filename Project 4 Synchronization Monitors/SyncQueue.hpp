#pragma once

#include <string>
#include <list>
#include "monitor.h"

class SyncQueue : public Monitor {
public:
    struct message{
        int queueID;        
        std::string producerID;
        std::string messageID;

        message(int _queueID, std::string _producerID, std::string _messageID);

        friend std::ostream& operator<<(std::ostream& os, const message& m);
    };

    SyncQueue(size_t queueSize, int queueID);
    void produce(message m);
    void consume(bool randomChoice, size_t index);
    const void read();

private:
    std::list<message> queue;
    int queueID;
    int queueSize = 0;
    int maxQSize = 0;
    Condition full, empty;
};