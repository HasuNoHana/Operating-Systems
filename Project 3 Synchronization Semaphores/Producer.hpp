#pragma once

#include <string>
#include "SharedQueues.hpp"

class Producer {
public:
    void produce(size_t queueID, std::string producerID, SharedQueues *sharedQueues);
};