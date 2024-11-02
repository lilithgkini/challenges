CC = gcc

TARGET = challenge
SRC = src/main.c


default: $(TARGET)


$(TARGET): $(SRC)
	$(CC) $(SRC) -o $@
	@strip $(TARGET) 


clean:
	rm $(TARGET)
