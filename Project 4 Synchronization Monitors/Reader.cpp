#include <thread>
#include <chrono>

#include "Reader.hpp"
#include "Random.hpp"

#define MIN_TIME 10
#define MAX_TIME 100

// read message every random period of time
void Reader::read(size_t queueID, SharedQueues *sharedQueues) {
    while(true) {
        sharedQueues->read(queueID);
        std::this_thread::sleep_for(std::chrono::milliseconds(genRandNum(MIN_TIME, MAX_TIME)));
    }
}