# A simple Makefile
# Aaron Kim
# GMU SMS Project
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc

CFLAGS = -o
TARGET = SMSproject
LIBS=-lm

all: $(TARGET)
$(TARGET): $(TARGET).c GMUsms.o 
	$(CC) $(CFLAGS) $(TARGET) $(TARGET).c GMUsms.o -Wall

clean:
	rm $(TARGET)


