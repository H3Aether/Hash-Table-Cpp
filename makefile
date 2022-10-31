CC = g++
CFLAGS = -Wall -O3

SOURCES = main.cpp\
	./src/hash_function.cpp\
	./src/NASA_JPL_SBDB/NASA_JPL_SBDB.cpp\

OBJECTS = $(SOURCES: .cpp = .o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@