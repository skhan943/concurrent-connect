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
}

int main() {
    std::cout << "I am the server. Type anything to shut down." << std::endl;

    Socket server("127.0.0.1", 2000);
    server.bind_and_listen();

    std::cin.get();

    server.close();
    return 0;
}