#include <iostream>
#include <thread>
#include <chrono>

#include "SharedQueues.hpp"
#include "Reader.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "Random.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Wrong number of arguments";
        return 0;
    }
    SharedQueues *sharedQueues = new SharedQueues(atoi(argv[1]));

    std::thread readerA(&Reader::read, Reader(), 0, sharedQueues);
    std::thread readerB(&Reader::read, Reader(), 1, sharedQueues);
    std::thread producerA(&Producer::produce, Producer(), 0, "ProducerA", sharedQueues);
    std::thread producerB(&Producer::produce, Producer(), 1, "ProducerB", sharedQueues);
    std::thread consumer(&Consumer::consume, Consumer(), sharedQueues);

    readerA.join();
    readerB.join();
    producerA.join();
    producerB.join();
    consumer.join();

    delete sharedQueues;
}