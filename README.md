
# Concurrent Connect

This project implements a multi-threaded Connect Four game server and client in C++. The server manages multiple game sessions concurrently, pairing players as they connect and overseeing the game logic. The communication between the server and clients is handled using TCP sockets. Semaphores are used to manage shared resources.

## Design

### Threading

The server is designed to handle multiple game sessions simultaneously using threads. Each game session runs in a separate thread, allowing multiple pairs of players to play concurrently without interfering with each other.

- **GameThread**: A custom thread class that manages the gameplay between two connected players. Each `GameThread` is responsible for one game session and handles all communication between the players, including move validation and game state updates.

- **Server Thread**: The main server thread is responsible for accepting incoming connections and placing players in a queue. When two players are available, they are assigned to a `GameThread` and their game begins in a new thread.

### Semaphores

Semaphores are used to manage shared resources and ensure that the game state is updated atomically. This prevents race conditions and ensures that the game logic remains consistent even when multiple threads are active.

- **Player Queue Management**: Semaphores ensure that access to the player queue is synchronized, so that no two threads can simultaneously modify the queue.

### Sockets

The `Socket` class abstracts the details of TCP socket communication between the server and clients.

- **Socket Class**: 
  - **Construction**: Handles both server-side (binding and listening) and client-side (connecting) socket operations.
  - **Communication**: Provides methods for reading from and writing to sockets using string-based data.
  - **Lifecycle Management**: Ensures that sockets are properly created, used, and closed.
    
The server uses these sockets to manage client connections and data transmission, ensuring a smooth and responsive gameplay experience.

## Gameplay and Features

### Gameplay

- **Connect Four Rules**: The game follows traditional Connect Four rules. Players take turns dropping discs into a vertical grid, and the first player to align four of their discs horizontally, vertically, or diagonally wins.

- **Turn-based Play**: The server coordinates the game by informing each player when it's their turn. Players receive the current board state, make a move, and send their move back to the server.

- **Win Detection**: After each move, the server checks if the move results in a win. If a win is detected, the game ends, and both players are notified of the result.

### Features

- **Concurrent Games**: The server supports multiple simultaneous games, with each game running in its own thread.
- **Socket Communication**: Communication between the client and server is done via TCP sockets, ensuring reliable data transmission.
- **Input Validation**: The server checks each move for validity, ensuring that players only make legal moves within the bounds of the game board.

## Build and Run

### Prerequisites

- **C++17** or later
- **g++** compiler or another compatible C++ compiler
- **Make** (for building the project)

### Building the Project

To build both the server and client executables, use the following command:

```bash
make
```

This will compile the source code and create two executables: `Server` and `Player`.

### Running the Server

Start the Connect Four server:

```bash
./Server
```

The server will listen for incoming connections on `127.0.0.1` and port `2000`. It will pair up connected players and start a new game for each pair.

### Running the Client

To connect to the server and start playing:

```bash
./Player
```

The client will connect to the server, display the current state of the Connect Four board, and allow the player to make moves.

### Clean Up

To remove the compiled binaries and object files, use:

```bash
make clean
```
