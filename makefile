CC = g++
#CFLAGS = $$(pkg-config --cflags gtk+-3.0)
#$ cc  -o hello `pkg-config --libs gtk4`

CFLAGS = `pkg-config --cflags gtk+-3.0`
OFLAGS = `pkg-config --libs gtk+-3.0`

PG = main

all: 
	$(CC) $(CFLAGS) $(PG).cpp  -o $(PG).o $(OFLAGS); ./$(PG).o

run:
	sudo ./$(PG).o