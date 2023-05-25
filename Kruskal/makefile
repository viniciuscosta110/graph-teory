CC = g++
CFLAGS = -std=c++11 -Wall

TARGET = kruskal.bin
SRC = kruskal.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	del /Q *.o *.d kruskal.bin

%:
	@: