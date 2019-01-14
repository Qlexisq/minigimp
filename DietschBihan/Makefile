CC=gcc
CFLAGS=-Wall 


minigimp: main.o cellule.o
		$(CC) -o $@ $^

main.o: main.c cellule.c
	$(CC) -o $@ -c $< $(CFLAGS)

cellule.o: cellule.c cellule.h
	     $(CC) -o $@ -c $< $(CFLAGS)
 
clean:
	rm -rf *.o