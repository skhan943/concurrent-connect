#include "../include/Semaphore.h"
#include "../include/Thread.h"
#include "../include/Socket.h"
#include <iostream>
#include <vector>
#include <queue>

// Constants
const int NUM_ROWS = 6;
const int NUM_COLS = 7;

class GameThread : public Thread {
private:
    Socket& player1;
    Socket& player2;
    int currentPlayer;
    bool gameOver;
    int board[NUM_ROWS][NUM_COLS];

    std::string getBoardState() {
        std::string state;
        for (int i = NUM_ROWS - 1; i >= 0; i--) {
            for (int j = 0; j < NUM_COLS; j++) {
                state += std::to_string(board[i][j]) + " ";
            }
            state += "\n";
        }
        return state;
    }

    // Function to check for win
    bool check_win(int player){

        // Check horizontal
        for (int i = 0; i < NUM_ROWS; i++){
            for (int j = 0; j < NUM_COLS - 3; j++){
                if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player){
                    return true;
                }
            }
        }

        // Check vertical
        for (int i = 0; i < NUM_ROWS - 3; i++){
            for (int j = 0; j < NUM_COLS; j++){
                if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player){
                    return true;
                }
            }
        }

        // Check diagonal (up-right)
        for (int i = 0; i < NUM_ROWS - 3; i++){
            for (int j = 0; j < NUM_COLS - 3; j++){
                if (board[i][j] == player && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player){
                    return true;
                }
            }
        }

        // Check diagonal (up-left)
        for (int i = 0; i < NUM_ROWS - 3; i++){
            for (int j = 3; j < NUM_COLS; j++){
                if (board[i][j] == player && board[i+1][j-1] == player && board[i+2][j-2] == player && board[i+3][j-3] == player){
                    return true;
                }
            }
        }

        return false;
    }

    void makeMove(int column, int player) {
        for (int i = 0; i < NUM_ROWS; i++) {
            if (board[i][column] == 0) {
                board[i][column] = player;
                break;
            }
        }
    }

public:
    GameThread(Socket& p1, Socket& p2) 
        : Thread([this]() { this->ThreadMain(); }),
          player1(p1), player2(p2), currentPlayer(1), gameOver(false) {
        std::memset(board, 0, sizeof(board));
    }

    ~GameThread() {
        gameOver = true;
        player1.write("Server Closed");
        player2.write("Server Closed");
    }

    void ThreadMain() {
        try {
            std::string boardData = getBoardState();
            player1.write(boardData);
            player1.read(boardData); // Ack
            player2.write(boardData);
            player2.read(boardData); // Ack

            while (!gameOver) {
                Socket& currentSocket = (currentPlayer == 1) ? player1 : player2;
                Socket& otherSocket = (currentPlayer == 1) ? player2 : player1;

                currentSocket.write("yt");
                std::string moveData;
                currentSocket.read(moveData);
                int move = std::stoi(moveData);

                makeMove(move, currentPlayer);

                boardData = getBoardState();
                currentSocket.write(boardData);
                currentSocket.read(moveData); // Ack
                otherSocket.write(boardData);
                otherSocket.read(moveData); // Ack

                if (checkWin(currentPlayer)) {
                    std::string winMessage = "Player " + std::to_string(currentPlayer) + " wins!";
                    currentSocket.write(winMessage);
                    currentSocket.read(moveData); // Ack
                    otherSocket.write(winMessage);
                    otherSocket.read(moveData); // Ack
                    gameOver = true;
                }

                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        } catch (const std::exception& error) {
            std::cout << error.what() << std::endl;
        }
    }
}

// Main server function
int main() {
    std::cout << "I am the server. Type anything to shut down." << std::endl;

    try {
        // Create server
        Socket server("127.0.0.1", 2000);
        server.bind_and_listen();

        std::vector<GameThread*> games;
        std::queue<Socket*> player_queue;

        // Thread to handle incoming connections
        Thread serverThread([&server, &games, &player_queue]() {
            while (true) {
                try {
                    Socket* newConn = server.accept();
                    player_queue.push(newConn);

                    // Check if there are two players waiting
                    if (player_queue.size() >= 2) {
                        Socket* player1 = player_queue.front();
                        player_queue.pop();
                        Socket* player2 = player_queue.front();
                        player_queue.pop();

                        games.push_back(new GameThread(*player1, *player2));
                        std::cout << "A game has been started!" << std::endl;
                    }
                } catch (const std::exception& error) {
                    break;
                }
            }
        });

        // Wait for input to shutdown the server
        std::cin.get();

        // Shut down and clean up
        server.close();

        for (auto game : games) {
            delete game;
        }
        games.clear();

        while (!player_queue.empty()) {
            delete player_queue.front();
            player_queue.pop();
        }

    } catch (const std::exception& error) {
        std::cout << error.what() << std::endl;
    }

    return 0;
}