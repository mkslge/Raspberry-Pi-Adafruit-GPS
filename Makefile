CC = gcc
CFLAGS = -lm
EXEC = gps

SRC = gps.c 
OBJ = gps.o 

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)

test: $(EXEC)
	./$(EXEC)
