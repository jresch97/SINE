CC = gcc
CFLAGS = -ansi -pedantic -Wall -fPIC -g -I../COSINE
LDFLAGS = -L../COSINE -l:libcosine.a
SRC = main.c hash_table.c
OBJ = main.o hash_table.o ../COSINE/examples/int.o ../COSINE/examples/string.o

sine: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f sine $(OBJ)

.PHONY: clean
