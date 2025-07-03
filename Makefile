CC = gcc
CFLAGS = -ansi -pedantic -Wall
LDFLAGS = -lm
TARGET = treasure_hunt
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
    $(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

run: $(TARGET)
    ./$(TARGET)

clean:
    rm -f $(OBJECTS) $(TARGET)
