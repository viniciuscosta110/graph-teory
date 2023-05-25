CC = g++
CFLAGS = -std=c++11 -Wall

TARGET = dijkstra.bin
SRC = dijkstra.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	del /Q *.o *.d dijkstra.bin

%:
	@: