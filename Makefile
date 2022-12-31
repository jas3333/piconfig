CC=gcc
CFLAGS=-I. -Iinclude -Isrc

all: piconfig

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o main.o

blur.o: src/blur.c
	$(CC) $(CFLAGS) -c src/blur.c -o blur.o

corners.o: src/corners.c
	$(CC) $(CFLAGS) -c src/corners.c -o corners.o

fade.o: src/fade.c
	$(CC) $(CFLAGS) -c src/fade.c -o fade.o

file.o: src/file.c
	$(CC) $(CFLAGS) -c src/file.c -o file.o

opacity.o: src/opacity.c
	$(CC) $(CFLAGS) -c src/opacity.c -o opacity.o

shadows.o: src/shadows.c
	$(CC) $(CFLAGS) -c src/shadows.c -o shadows.o

animations.o: src/animations.c
	$(CC) $(CFLAGS) -c src/animations.c -o animations.o

piconfig: main.o animations.o blur.o corners.o fade.o file.o opacity.o shadows.o
	$(CC) $(CFLAGS) main.o animations.o blur.o corners.o fade.o file.o opacity.o shadows.o -lncurses -o piconfig

clean:
	rm -f *.o piconfig 
