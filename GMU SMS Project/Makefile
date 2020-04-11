# A simple Makefile
# Aaron Kim, G01154538
# CS 262, Lab Section 214
# Project 2
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc

CFLAGS = -o
TARGET = project2_akim56_214
LIBS=-lm

all: $(TARGET)
$(TARGET): $(TARGET).c GMUsms.o 
	$(CC) $(CFLAGS) $(TARGET) $(TARGET).c GMUsms.o -Wall

clean:
	rm $(TARGET)


