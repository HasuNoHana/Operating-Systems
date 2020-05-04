#pragma once

#include "SyncQueue.hpp"

class SharedQueues {
public:
    SharedQueues(size_t queueSize);
    // add message to queue
    void produce(size_t queueNr, SyncQueue::message m);
    // consume specific message from queue
    void consume(size_t queueNr, size_t index);
    // consume message from random queue
    void consumeRandom(size_t queueNr);
    // read message from queue
    const void read(size_t queueNr);

private:
    SyncQueue queues[2];
};