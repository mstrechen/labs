CC = g++
LIBDIRECTORY =includes
INCLUDES_CPP = benchmark.cpp listoftests.cpp textstyle.cpp cpuinfo.cpp
INCLUDES_O = $(INCLUDES_CPP:.cpp=.o)

FLAGS = -O1 -Wall -std=c++11
OUTPUT_FILE = main.out



all: main

main: main.o $(INCLUDES_O)
	$(CC) $(FLAGS) -I./$(LIBDIRECTORY) main.o $(INCLUDES_O) -o $(OUTPUT_FILE)

main.o: benchmark.o
	$(CC) $(FLAGS) -I./$(LIBDIRECTORY) -c main.cpp

benchmark.o:
	$(CC) $(FLAGS) -I./$(LIBDIRECTORY) -c $(LIBDIRECTORY)/benchmark.cpp

listoftests.o:
	$(CC) $(FLAGS) -I./$(LIBDIRECTORY) -c $(LIBDIRECTORY)/listoftests.cpp

textstyle.o:
	$(CC) $(FLAGS) -I./$(LIBDIRECTORY) -c $(LIBDIRECTORY)/textstyle.cpp

cpuinfo.o:
	$(CC) $(FLAGS) -I./$(LIBDIRECTORY) -c $(LIBDIRECTORY)/cpuinfo.cpp

clean: 
	rm -rf *.o *.out $(LIBDIRECTORY)/*.h.gch
