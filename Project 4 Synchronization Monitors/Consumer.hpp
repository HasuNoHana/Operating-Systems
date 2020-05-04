#pragma once

#include "SharedQueues.hpp"

class Consumer {
public:
    // consume messages every random period of time
    void consume(SharedQueues *sharedQueues);
};