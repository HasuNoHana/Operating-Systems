#pragma once

#include "SharedQueues.hpp"

class Consumer {
public:
    void consume(SharedQueues *sharedQueues);
};