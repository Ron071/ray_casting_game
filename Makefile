# Compiler and Flags
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files and output
SRC = game.cpp main.cpp maze.cpp player.cpp ray.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = game

# Build the executable
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(SFML_LIBS)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(EXEC)

# Run the game
run: $(EXEC)
	./$(EXEC)

