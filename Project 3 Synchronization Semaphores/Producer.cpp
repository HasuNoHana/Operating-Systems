#include <thread>
#include <chrono>

#include "Random.hpp"
#include "Producer.hpp"

#define MIN_TIME 10
#define MAX_TIME 100

void Producer::produce(size_t queueID, std::string producerID, SharedQueues *sharedQueues) {
    size_t nextMessageID = 0;
    while(true) {
        std::string messageID =  "Message_" + std::to_string(nextMessageID);
        SyncQueue::message m(queueID, producerID, messageID);

        sharedQueues->produce(queueID, m);
        nextMessageID++;
        std::this_thread::sleep_for(std::chrono::milliseconds(genRandNum(MIN_TIME, MAX_TIME)));
    }
}
