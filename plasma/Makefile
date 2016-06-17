LDFLAGS := -lSDL2 -lm
CFLAGS := -O3 -Werror -Wall -Wextra -pedantic -std=c90 -g

CFLAGS += -Wno-overlength-strings

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
