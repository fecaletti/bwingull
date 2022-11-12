# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = `wx-config --cxxflags --libs`

# The build target 
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
			$(CC) $(CFLAGS) -o $(TARGET).outm $(TARGET).cpp src/ponto/ponto.cpp src/rota/rota.cpp

clean:
			$(RM) $(TARGET)