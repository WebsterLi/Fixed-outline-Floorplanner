CC=g++
CFLAGS=-std=c++11 -c -Wall -O3
LDFLAGS=
SOURCES=main.cpp floorplan.cpp parser.cpp bstree.cpp operation.cpp output.cpp
OBJECTS=$(SOURCES:.cpp=.o)
			EXECUTABLE=SA

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
				$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
				$(CC) $(CFLAGS) $< -o $@

clean:
				rm ./*.o ./$(EXECUTABLE)


