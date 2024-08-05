#include "../include/Socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

// Constructor to create a socket and set up the server address
Socket::Socket(const std::string &ipAddress, unsigned int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Unable to create socket");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ipAddress.c_str(), &server_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address");
    }
}

// Constructor for accepted connections
Socket::Socket(int sockfd) : sockfd(sockfd) {}

// Destructor to close the socket
Socket::~Socket(){
    this->close()
}

// Method to bind and listen (for server)
void Socket::bind_and_listen() {
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("Binding failed");
    }
    if (listen(sockfd, 5) < 0) {
        throw std::runtime_error("Listening failed");
    }
}

// Method to accept a new connection
Socket* Socket::accept() {
    int new_sockfd = ::accept(sockfd, nullptr, nullptr);
    if (new_sockfd < 0){
        throw std::runtime_error("Failed to accept connection"); 
    }
    return new Socket(new_sockfd);
}

// Method to open the socket connection (for players)
void Socket::open() {
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("Connection failed");
    }
}

// Method to close the socket connection
void Socket::close() {
    ::close(sockfd);
}