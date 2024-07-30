#include "../include/Semaphore.h"

// Constructor to initialize sempahore count
Semaphore::Semaphore(int count) : count(count) {}

// Notify method to increment count and notify one waiting thread
void Semaphore::notify() {
    std::lock_guard<std::mutex> lock(mtx);
    ++count;
    cv.notify_one();
}

// Wait method to decrement count or block if count <= 0
void Semaphore::wait() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() {return count > 0;});
    --count;
}