CC:=gcc
CFLAGS:=-std=c11 -Wall -Wextra -Wpedantic -Werror -O0 -g -Iinclude -MMD -MP

TARGET:=ring_buffer

SRC:=$(wildcard src/*.c)
OBJ:=$(patsubst %.c,build/%.o,$(SRC))
DEP:=$(OBJ:.o=.d)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf build $(TARGET)

-include $(DEP)