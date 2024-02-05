CC = gcc
CFLAGS = -Wall -Wextra -g -I\MinGW\lib\gcc\mingw32\6.3.0\include -Wl,--stack,32777216

all: Rainha

Rainha: backtrack.o
	$(CC) $(CFLAGS) -o Rainha backtrack.o

main.o: backtrack.c
	$(CC) $(CFLAGS) -c backtrack.c

clean:
	rm -f Rainha *.o
