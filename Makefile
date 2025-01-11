OBJECT1=client
OBJECT2=server

FILE=tcp.c

all:
	$(CC) -o $(OBJECT1) $(OBJECT1).c $(FILE)
	$(CC) -o $(OBJECT2) $(OBJECT2).c $(FILE)