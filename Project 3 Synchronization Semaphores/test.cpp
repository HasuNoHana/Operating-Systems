#include <iostream>
#include <thread>
#include <chrono>

#include "SharedQueues.hpp"
#include "Random.hpp"

#define MIN_TIME 10
#define MAX_TIME 100

void reader(size_t queueID, SharedQueues *sharedQueues) {
    while(true) {
        sharedQueues->read(queueID);
        std::this_thread::sleep_for(std::chrono::milliseconds(genRandNum(MIN_TIME, MAX_TIME)));
    }
}

void writer_producer(size_t queueID, std::string producerID, SharedQueues *sharedQueues) {
    size_t nextMessageID = 0;
    while(true) {
        std::string messageID =  "Message_" + std::to_string(nextMessageID);
        SyncQueue::message m(queueID, producerID, messageID);

        sharedQueues->produce(queueID, m);
        nextMessageID++;
        std::this_thread::sleep_for(std::chrono::milliseconds(genRandNum(MIN_TIME, MAX_TIME)));
    }
}

void writer_consumer(/*size_t queueID, */SharedQueues *sharedQueues) {
    while(true) {
        sharedQueues->consumeRandom(0);
        sharedQueues->consumeRandom(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(genRandNum(MIN_TIME, MAX_TIME)));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Wrong number of arguments";
        return 0;
    }

    SharedQueues *sharedQueues = new SharedQueues(atoi(argv[1]));
    std::thread readerA(reader, 0, sharedQueues);
    std::thread readerB(reader, 1, sharedQueues);
    std::thread producerA(writer_producer, 0, "ProducerA", sharedQueues);
    std::thread producerB(writer_producer, 1, "ProducerB", sharedQueues);
    std::thread consumer(writer_consumer, sharedQueues);

    readerA.join();
    readerB.join();
    producerA.join();
    producerB.join();
    consumer.join();

    delete sharedQueues;
}