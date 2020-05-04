#include <random>
#include "Random.hpp"

int genRandNum(int min, int max) {
    // C++11 way of generating random numbers
    // rand() is not thread safe so it cannot be used for multithreading environment
    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}