#pragma once

#include <string>
#include "SharedQueues.hpp"

class Producer {
public:
    // produce message every random period of time
    void produce(size_t queueID, std::string producerID, SharedQueues *sharedQueues);
};