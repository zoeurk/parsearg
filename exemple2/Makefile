CC=gcc
ARG=-g -Wall -Wpadded -ansi

all:libparser.so
	 $(CC) $(ARG) basex.c -o basex -L. -lparsearg 

libparser.so:
	$(CC) $(ARG) -fPIC -c parsearg.c
	$(CC) $(ARG) -o libparsearg.so -shared parsearg.o

clean:
	rm -fv libparsearg.so parsearg.o basex
