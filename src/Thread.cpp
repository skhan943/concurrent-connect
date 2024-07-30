#include "../include/Thread.h"

// Constructor to intialize thread with a given function
Thread::Thread(std::function<void()> func) : th(func) {}

Thread::~Thread() {
    if (th.joinable()) {
        th.join();
    }
}

void Thread::join() {
    if (th.joinable()) {
        th.join();
    }
}