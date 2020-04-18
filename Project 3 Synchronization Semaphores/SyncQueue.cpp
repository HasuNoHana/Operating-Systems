#include "SyncQueue.hpp"
#include <iostream>
#include <iterator>

#include "Random.hpp"

SyncQueue::SyncQueue(size_t queueSize) {
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, queueSize);
    sem_init(&mutexEntry, 0, 1);
    sem_init(&mutexCounter, 0, 1);
}

SyncQueue::~SyncQueue() {
    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutexEntry);
    sem_destroy(&mutexCounter);
}

void SyncQueue::produce(SyncQueue::message m) {
    sem_wait(&empty);
    sem_wait(&mutexEntry);

    std::cout << "Writer:\nAdding new message:\n" << m << std::endl;
    queue.push_back(m);

    sem_post(&mutexEntry);
    sem_post(&full);
}

void SyncQueue::consume(bool randomChoice, size_t index) {
    sem_wait(&full);
    sem_wait(&mutexEntry);

    if (randomChoice)
        index = genRandNum(0, queue.size() - 1);
    auto iter = queue.begin();
    std::advance(iter, index);

    std::cout << "Consumer:\nConsuming message:\n" << *iter << std::endl;
    queue.erase(iter);

    sem_post(&mutexEntry);
    sem_post(&empty);
}

const void SyncQueue::read() {
    sem_wait(&mutexCounter);

    readersCounter++;
    if (readersCounter == 1)
        sem_wait(&mutexEntry);
    
    sem_post(&mutexCounter);

    std::cout << "Reader:\nReading messages from queue: " << std::endl;
    for (auto m : queue)
        std::cout << m;
    std::cout << std::endl;

    sem_wait(&mutexCounter);

    readersCounter--;
    if (readersCounter == 0)
        sem_post(&mutexEntry);

    sem_post(&mutexCounter);
}


SyncQueue::message::message(int _queueID, std::string _producerID, std::string _messageID): 
        queueID(_queueID), producerID(_producerID), messageID(_messageID){};

std::ostream& operator<<(std::ostream& os, const SyncQueue::message& m)
{
  os << "Queue ID: " << m.queueID << " Message ID: " << m.messageID << " Producer ID: " << m.producerID <<  std::endl;
  return os;
}