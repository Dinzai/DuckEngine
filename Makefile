CXX = g++
CC  = gcc

CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
CFLAGS   = -O2 -Iinclude

LDFLAGS = -lglfw -lGL -ldl -lpthread -lX11 -lXinerama -lXcursor -lXi

SRC_CPP = main.cpp window.cpp
SRC_C   = src/glad.c

OBJ_CPP = $(SRC_CPP:.cpp=.o)
OBJ_C   = $(SRC_C:.c=.o)

TARGET = app

all: $(TARGET)

$(TARGET): $(OBJ_CPP) $(OBJ_C)
	$(CXX) $(OBJ_CPP) $(OBJ_C) -o $(TARGET) $(LDFLAGS)

# Compile C++ sources
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C sources
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CPP) $(OBJ_C) $(TARGET)

.PHONY: all clean
