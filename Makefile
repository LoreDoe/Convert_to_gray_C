CC = gcc
CFLAGS = -Wall
LDFLAGS = 

all: image_processor

image_processor: image.o main.o
    $(CC) $(CFLAGS) -o image_processor image.o main.o $(LDFLAGS)

image.o: image.c image.h
    $(CC) $(CFLAGS) -c image.c

main.o: main.c image.h
    $(CC) $(CFLAGS) -c main.c

clean:
    rm -f *.o image_processor
