CC = g++
CFLAGS = -Wall

SOURCES = main.cpp\
	hash_function.cpp\
	hash_table.cpp\
	hash_table_element.cpp\

OBJECTS = $(SOURCES: .cpp = .o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@