CC = g++
LIBDIRECTORY =includes

FLAGS = -O2 -Wall -std=c++11
OUTPUT_FILE = main.out



all: main

main: main.o $(INCLUDES_O)
	$(CC) $(FLAGS) -I./$(LIBDIRECTORY) main.o -o $(OUTPUT_FILE)

main.o:
	$(CC) $(FLAGS) -I./$(LIBDIRECTORY) -c main.cpp

clean: 
	rm -rf *.o *.out $(LIBDIRECTORY)/*.h.gch
