OBJECT1=client
OBJECT2=server

FILE=tcp.c
OPT=-lpthread -lrt

all:
	$(CC) -o $(OBJECT1) $(OBJECT1).c $(FILE) $(OPT)
	$(CC) -o $(OBJECT2) $(OBJECT2).c $(FILE) $(OPT)