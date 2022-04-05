CC=gcc
CFLAGS=-Ofast -Wall -Wstrict-prototypes -fopenmp
PRG=cr4ck

OBJECTS=sha1.o sha1-pbkdf2.o main.o utils.o fastpbkdf2.o gen.o decode.o
LIBS=-lcrypto -lm -fopenmp 


$(PRG): $(OBJECTS)
	$(CC) -o $(PRG) $(OBJECTS) $(LIBS)


clean:
	rm -f $(OBJECTS) $(PRG)
