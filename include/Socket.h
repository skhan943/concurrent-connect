#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Socket {
public:
    // Constructor to initialize socket with IP address and port
    Socket(const std::string &ipAddress, unsigned int port);

    // Constructor for accepted connections
    Socket(int sockfd);

    // Destructor to close the socket
    ~Socket();

    // Method to write data
    int write(const std::string &data);

    // Method to read data
    int read(std::string &data);

    // Method to open the socket connection (for players)
    void open();

    // Method to bind and listen (for server)
    void bind_and_listen();

    // Method to accept a new connection
    Socket* accept();

    // Method to close the socket connection
    void close();

private:
    int sockfd; // Socket file descriptor
    struct sockaddr_in server_addr; // Server address structure
}

#endif // SOCKET_H