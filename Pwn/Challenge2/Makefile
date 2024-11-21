CC = gcc
LDFLAGS = -lpthread -Wl,--dynamic-linker,$(realpath lib/ld-linux-x86-64.so.2) -Xlinker -rpath=$(realpath lib/)

TARGET = challenge
SRC = src/main.c

default: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(LDFLAGS) $(SRC) -o $@

clean:
	rm $(TARGET)
