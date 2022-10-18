CC = gcc
CFLAGS = -g -Wall
BIN = RBT
OBJ = RBT.o
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(BIN): main.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

do:
	./$(BIN)

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN)

clean:
	rm $(BIN) $(OBJ)