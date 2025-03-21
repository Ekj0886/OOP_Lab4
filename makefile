# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

# Sources
SRC = main.cpp $(SRC_DIR)/mat_gen.cpp
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/checker.o $(OBJ_DIR)/CNumpy.o 

# Output executable
OUTPUT = Lab4

# Default target
all: clean $(OUTPUT)

# Linking the object files to create the executable
$(OUTPUT): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(OBJ)

# Compile main.cpp
$(OBJ_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c main.cpp -o $(OBJ_DIR)/main.o

# Link with the precompiled checker.o (no need for checker.cpp)
$(OBJ_DIR)/checker.o: $(OBJ_DIR)/checker.o

# Compile CNumpy.cpp
$(OBJ_DIR)/CNumpy.o: $(SRC_DIR)/CNumpy.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/CNumpy.cpp -o $(OBJ_DIR)/CNumpy.o

# Clean object files and executable, excluding checker.o
clean:
	rm -f obj/CNumpy.o obj/CNumpy.d obj/main.o obj/main.d

.PHONY: all clean

