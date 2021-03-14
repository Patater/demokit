LDFLAGS := -lSDL2 -lm
CFLAGS := -O3 -Werror -Wall -Wextra -pedantic -std=c90 -g

CFLAGS += $(shell sdl2-config --cflags)
LIBS += $(shell sdl2-config --libs)
CFLAGS += $(LIBS)

CFLAGS += -Wno-overlength-strings
CFLAGS += -fsanitize=undefined -fno-sanitize-recover=undefined

all: plasma

run: plasma
	./plasma

OBJS := plasma.c plasmpal.c
INC := plasmpal.h

plasma: $(OBJS) $(INC)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-rm -f plasma *.o
