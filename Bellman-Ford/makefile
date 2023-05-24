CC = g++
CFLAGS = -std=c++11 -Wall

TARGET = bellman_ford.bin
SRC = bellman_ford.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	del /Q *.o *.d bellman_ford.bin

%:
	@:
