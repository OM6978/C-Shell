CC = gcc
CFLAGS = -g
EXECUTABLE = shell
SOURCES = main.c utils.c log.c commands.c history.c process.c
OBJECTS = $(SOURCES:.c=.o)
GENS = history.txt log.txt

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "Linking $(EXECUTABLE)..."
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
# 	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm -f $(OBJECTS) $(EXECUTABLE)

deepclean:
	@echo "Performing Deep Clean..."
	rm -f $(OBJECTS) $(EXECUTABLE) $(GENS)

.PHONY: all clean