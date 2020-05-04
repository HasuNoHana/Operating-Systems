#include "SyncQueue.hpp"
#include <iostream>
#include <iterator>

#include "Random.hpp"

SyncQueue::SyncQueue(size_t _maxQSize, int _queueID) : Monitor(){
    maxQSize = _maxQSize;
    queueID = _queueID;
}

void SyncQueue::produce(SyncQueue::message m) {
    enter();
    // check if there is still space in queue
    if (queueSize == maxQSize)
        wait(full);

    // produce new message
    std::cout << "Writer:\nAdding new message:\n" << m << std::endl;
    queue.push_back(m);
    queueSize++;

    // wake up consumers and readers
    if (queueSize == 1)
        signal(empty);
    leave();
}

void SyncQueue::consume(bool randomChoice, size_t index) {
    enter();
    // check if there is anything in queue
    if (queueSize == 0)
        wait(empty);

    // consume message
    if (randomChoice)
        index = genRandNum(0, queue.size() - 1);
    auto iter = queue.begin();
    std::advance(iter, index);

    std::cout << "Consumer:\nConsuming message:\n" << *iter << std::endl;
    queue.erase(iter);
    queueSize--;

    // wake up producers
    if (queueSize == maxQSize - 1)
        signal(full);
    leave();
}

const void SyncQueue::read() {
    enter();

    // read message
    std::cout << "Reader:\nReading messages from queue: " << queueID << std::endl;
    for (auto m : queue)
        std::cout << m;
    std::cout << std::endl;

    leave();
}


SyncQueue::message::message(int _queueID, std::string _producerID, std::string _messageID): 
        queueID(_queueID), producerID(_producerID), messageID(_messageID){};

std::ostream& operator<<(std::ostream& os, const SyncQueue::message& m)
{
  os << "Queue ID: " << m.queueID << " Message ID: " << m.messageID << " Producer ID: " << m.producerID <<  std::endl;
  return os;
}