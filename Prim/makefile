CC = g++
CFLAGS = -std=c++11 -Wall

TARGET = prim
SRC = prim.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	del /Q *.o *.d prim.exe

%:
	@:
