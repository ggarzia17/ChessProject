# A line starting with a has is a comment, we'll build up
# the below example

TARGET = chess
SRC_FILES = main.cpp Chessboard.cpp Square.cpp Game.cpp

# DO NOT EDIT BELOW HERE
CXX = g++
CFLAGS = -Wall -g -std=c++11
OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CFLAGS) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)

# DEPENDENCIES
Game.o: Game.cpp Game.h Chessboard.h
Square.o: Square.cpp Square.h
Chessboard.o: Chessboard.cpp Chessboard.h Square.h
main.o: main.cpp Game.h