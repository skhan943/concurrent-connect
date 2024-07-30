#include "../include/Thread.h"

// Constructor to intialize thread with a given function
Thread::Thread(std::function<void()> func) : th(func) {}

// Destructor to join the thread if joinable
Thread::~Thread() {
    if (th.joinable()) {
        th.join();
    }
}

// Method to join the thread
void Thread::join() {
    if (th.joinable()) {
        th.join();
    }
}