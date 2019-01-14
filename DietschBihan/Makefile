CC=gcc
CFLAGS=-Wall 


./bin/minigimp: ./src/main.o ./src/histogramme.o
		$(CC) -o $@ $^

./src/histogramme.o: ./src/histogramme.c ./src/histogramme.h
	    $(CC) -o $@ -c $< $(CFLAGS)

./src/main.o: ./src/main.c ./src/histogramme.h
		$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o