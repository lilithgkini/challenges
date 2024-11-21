CC = gcc
FLAG = -z execstack

TARGET = challenge
SRC = src/main.c


default: $(TARGET)


$(TARGET): $(SRC)
	@$(CC) $(FLAG) $(SRC) -o $@
	@strip $(TARGET) 


clean:
	rm $(TARGET)
