LDFLAGS := -lSDL2 -lm
CFLAGS := -O3 -Werror -Wall -Wextra -pedantic -std=c90 -g

CFLAGS += $(shell sdl2-config --cflags)
LIBS += $(shell sdl2-config --libs)
CFLAGS += $(LIBS)

CFLAGS += -Wno-overlength-strings
CFLAGS += -fsanitize=undefined -fno-sanitize-recover=undefined

PROGRAM := stars

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

OBJS := $(PROGRAM).c
INC :=

$(PROGRAM): $(OBJS) $(INC)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-rm -f $(PROGRAM) *.o
