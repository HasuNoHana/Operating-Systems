#include "SharedQueues.hpp"
#include <iostream>
#include <iterator>

SharedQueues::SharedQueues(size_t queueSize)
    : queues { SyncQueue(queueSize, 0), SyncQueue(queueSize, 1) }
{ }

// add message to queue
void SharedQueues::produce(size_t queueNr, SyncQueue::message m) {
    queues[queueNr].produce(m);
}

// consume message from random queue
void SharedQueues::consumeRandom(size_t queueNr) {
    queues[queueNr].consume(true, 0);
}

// consume specific message from queue
void SharedQueues::consume(size_t queueNr, size_t index) {
    queues[queueNr].consume(false, index);
}

// read message from queue
const void SharedQueues::read(size_t queueNr) {
    queues[queueNr].read();
}
