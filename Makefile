CXX := gcc
CXXFLAGS := -Wall -Wextra -O2 -std=c99

BIN := bin
SRC := src
INCLUDE := include

LIBRARIES :=
EXECUTABLE := main

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	rm -rf $(BIN)/*