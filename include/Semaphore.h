#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

// Semaphore class for synchronizing threads
class Semaphore {
public:
    // Constructor to initialize the semaphore with a given count
    Semaphore(int count = 0);

    // Method to increment the semaphore count and notify waiting threads
    void notify();

    // Method to decrement the semaphore count and wait if the count is zero
    void wait();

private:
    std::mutex mtx; // Mutex to protect shared data
    std::condition_variable cv; // Condition variable for blocking threads
    int count; // Semaphore count
};

#endif // SEMAPHORE_H
