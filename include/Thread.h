#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <functional>

// Thread class for managing threads
class Thread {
public:
    // Constructor to create a thread with a given function
    Thread(std::function<void()> func);

    // Destructor to join the thread if joinable
    virtual ~Thread();

    // Method to join the thread
    void join();

protected:
    void start();

private:
    std::thread th; // Thread object
};

#endif // THREAD_H
