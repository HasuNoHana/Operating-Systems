#include "SharedQueues.hpp"
#include <iostream>
#include <iterator>

SharedQueues::SharedQueues(size_t queueSize)
    : queues { SyncQueue(queueSize, 0), SyncQueue(queueSize, 1) }
{ }

void SharedQueues::produce(size_t queueNr, SyncQueue::message m) {
    queues[queueNr].produce(m);
}

void SharedQueues::consumeRandom(size_t queueNr) {
    queues[queueNr].consume(true, 0);
}

void SharedQueues::consume(size_t queueNr, size_t index) {
    queues[queueNr].consume(false, index);
}

const void SharedQueues::read(size_t queueNr) {
    queues[queueNr].read();
}
