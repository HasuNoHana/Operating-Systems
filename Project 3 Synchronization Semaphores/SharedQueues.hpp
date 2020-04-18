#pragma once

#include "SyncQueue.hpp"

class SharedQueues {
public:
    SharedQueues(size_t queueSize);
    void produce(size_t queueNr, SyncQueue::message m);
    void consume(size_t queueNr, size_t index);
    void consumeRandom(size_t queueNr);
    const void read(size_t queueNr);

private:
    SyncQueue queues[2];
};