# Makefile  for workshop3 COMP20007
# Andrew Turpin
# March 2015

OBJ     = graph.o heap.o cover.o set.o dijkstra.o main.o
SRC     = graph.c heap.c cover.c set.c dijkstra.c main.c
EXE     = dfsMaze 

CC    = g++
CDEFS = -Wall -m32 -O2

maze:   $(OBJ) Makefile
	$(CC) $(CDEFS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE)

test: $(EXE)
	./$(EXE) 10
