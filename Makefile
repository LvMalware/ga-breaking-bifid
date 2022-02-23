INCLUDES=-Ilib
SOURCES=src/*.c main.c
OUTPUT=bfbreak
CFLAGS=-Wall $(INCLUDES) -g -O3 -o $(OUTPUT)

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

test: all
	./$(OUTPUT)

clean:
	find . -iname '*~' -delete
	rm -rf $(OUTPUT)
