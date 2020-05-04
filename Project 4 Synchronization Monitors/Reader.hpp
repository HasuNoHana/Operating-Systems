#pragma once

#include "SharedQueues.hpp"

class Reader {
public:
    // read message every random period of time
    void read(size_t queueID, SharedQueues *sharedQueues);
};