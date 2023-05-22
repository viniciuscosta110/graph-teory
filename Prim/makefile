CC = g++
CFLAGS = -std=c++11 -Wall

TARGET = prim.bin
SRC = prim.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm /Q *.o *.d prim.bin

%:
	@:
