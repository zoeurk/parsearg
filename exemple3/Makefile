CC=gcc
ARG=-g -Wall -Wpadded -Wextra

all:libparser.so
	 $(CC) $(ARG) math.c -o math -L. -lparsearg -lm

libparser.so:
	$(CC) $(ARG) -fPIC -c parsearg.c
	$(CC) $(ARG) -o libparsearg.so -shared parsearg.o

clean:
	rm -fv libparsearg.so parsearg.o math
