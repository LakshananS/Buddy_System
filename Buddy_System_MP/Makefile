CC = gcc
CFLAGS = -Iinclude -g
SRC = src
OBJ = $(SRC)/buddy_system.o $(SRC)/list.o $(SRC)/virtual_mem.o $(SRC)/main.o

all: buddy_system

buddy_system: $(OBJ)
	$(CC) $(CFLAGS) -o buddy_system $(OBJ)

$(SRC)/buddy_system.o: $(SRC)/buddy_system.c include/buddy_system.h
	$(CC) $(CFLAGS) -c $(SRC)/buddy_system.c -o $(SRC)/buddy_system.o

$(SRC)/list.o: $(SRC)/list.c include/list.h
	$(CC) $(CFLAGS) -c $(SRC)/list.c -o $(SRC)/list.o

$(SRC)/virtual_mem.o: $(SRC)/virtual_mem.c include/virtual_mem.h
	$(CC) $(CFLAGS) -c $(SRC)/virtual_mem.c -o $(SRC)/virtual_mem.o

$(SRC)/main.o: $(SRC)/main.c include/buddy_system.h
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $(SRC)/main.o

clean:
	rm -f $(SRC)/*.o buddy_system
