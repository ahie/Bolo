CC=g++
CFLAGS=-std=c++11 -c
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=$(shell find -name '*.cpp')
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bolo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o bolo

