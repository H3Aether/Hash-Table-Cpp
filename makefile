CC = g++
CFLAGS = -Wall

SOURCES = main.cpp\
	./src/hash_function.cpp\
	./src/hash_table.cpp\
	./src/hash_table_element.cpp\

OBJECTS = $(SOURCES: .cpp = .o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@