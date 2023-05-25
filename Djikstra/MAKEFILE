CC = g++
CFLAGS = -std=c++11 -Wall

TARGET = djikstra.bin
SRC = djikstra.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	del /Q *.o *.d djikstra.bin

%:
	@: