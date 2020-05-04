#include <thread>
#include <chrono>
#include <iostream>

#include "Consumer.hpp"
#include "Random.hpp"

#define MIN_TIME 10
#define MAX_TIME 100

// consume messages every random period of time
void Consumer::consume(SharedQueues *sharedQueues) {
    while(true) {
        sharedQueues->consumeRandom(0);
        sharedQueues->consumeRandom(1);

        std::this_thread::sleep_for(std::chrono::milliseconds(genRandNum(MIN_TIME, MAX_TIME)));
    }
}