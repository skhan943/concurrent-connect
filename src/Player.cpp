#include "../include/Socket.h"
#include "../include/Semaphore.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "I am a player" << std::endl;

    try {
        // Create and open a connection with the server
        Socket socket("127.0.0.1", 2000);
        socket.open();

        std::string boardData;
        
        // Read initial board state from server
        socket.read(boardData);
        std::cout << "Current state of board:" << std::endl;
        std::cout << boardData << std::endl;

        socket.write("ack");

        while (true) {
            std::string message;
            socket.read(message);

            if (message == "yt") {
                // Get player's move
                int move;
                std::cout << "Enter your move (column number from 0 to 6): ";
                std::cin >> move;
                std::cout << "\n";

                // Send move to server
                socket.write(std::to_string(move));
            } else {
                std::cout << message << std::endl;

                if (message == "Player 1 wins!" || message == "Player 2 wins!" || message == "Server Closed") {
                    break;
                }

                socket.write("ack");
            }
        }

        // Close connection
        socket.close();
        return 0;
    } catch (const std::runtime_error& error) {
        std::cout << error.what() << std::endl;
    }
}