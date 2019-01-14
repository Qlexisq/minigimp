CC=gcc
CFLAGS=-Wall 


./bin/minigimp: ./src/main.o ./src/histogram.o ./src/image.o
		$(CC) -o $@ $^

./src/histogram.o: ./src/histogram.c ./src/histogram.h
	    $(CC) -o $@ -c $< $(CFLAGS)

./src/image.o: ./src/image.c ./src/image.h
	    $(CC) -o $@ -c $< $(CFLAGS)

./src/main.o: ./src/main.c ./src/histogram.h ./src/image.h
		$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o