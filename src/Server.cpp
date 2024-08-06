#include "../include/Semaphore.h"
#include "../include/Thread.h"
#include "../include/Socket.h"
#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::cout << "I am the server. Type anything to shut down." << std::endl;

    Socket server("127.0.0.1", 2000);
    server.bind_and_listen();

    std::cin.get();

    server.close();
    return 0;
}