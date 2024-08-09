# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executables
SERVER = server
CLIENT = client

# Targets
all: $(SERVER) $(CLIENT)

$(SERVER): $(BUILD_DIR)/Server.o $(BUILD_DIR)/Socket.o $(BUILD_DIR)/Thread.o $(BUILD_DIR)/Semaphore.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CLIENT): $(BUILD_DIR)/Player.o $(BUILD_DIR)/Socket.o $(BUILD_DIR)/Thread.o $(BUILD_DIR)/Semaphore.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(SERVER) $(CLIENT)

.PHONY: all clean