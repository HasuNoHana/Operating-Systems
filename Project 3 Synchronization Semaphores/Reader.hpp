#pragma once

#include "SharedQueues.hpp"

class Reader {
public:
    void read(size_t queueID, SharedQueues *sharedQueues);
};