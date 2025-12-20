CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra -pedantic -std=c11
THREAD_FLAGS := -pthread
INCLUDES := -Iinclude -Isrc

SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=build/%.o)
LIB := libschedlat.a

.PHONY: all lib example clean

all: lib example

lib: $(LIB)

$(LIB): $(OBJ)
	@rm -f $@
	ar rcs $@ $^

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) $(INCLUDES) $(THREAD_FLAGS) -c $< -o $@

example: lib
	$(CC) $(CFLAGS) $(INCLUDES) examples/basic.c -L. -lschedlat $(THREAD_FLAGS) -o examples/basic

build:
	mkdir -p build

clean:
	rm -rf build $(LIB) examples/basic
