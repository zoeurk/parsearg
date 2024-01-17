CC=gcc
ARG=-g -Wall -Wpadded -Wextra -pedantic -std=c90

all:libparser.so
	 $(CC) $(ARG) prog.c -o prog -L. -lparsearg 

libparser.so:
	$(CC) $(ARG) -fPIC -c parsearg.c
	$(CC) $(ARG) -o libparsearg.so -shared parsearg.o

clean:
	rm -fv libparsearg.so parsearg.o prog
