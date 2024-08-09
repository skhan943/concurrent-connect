# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Directories
SRC_DIR = ../src
INC_DIR = ../include
BUILD_DIR = .

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executables
SERVER = Server
CLIENT = Player

# Targets
all: print_info $(SERVER) $(CLIENT)

print_info:
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@ls -R $(SRC_DIR)

$(SERVER): Server.o Socket.o Thread.o Semaphore.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CLIENT): Player.o Socket.o Thread.o Semaphore.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f *.o $(SERVER) $(CLIENT)

.PHONY: all clean print_info
