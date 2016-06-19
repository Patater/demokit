LDFLAGS := -lSDL2 -lm
CFLAGS := -O3 -Werror -Wall -Wextra -pedantic -std=c90 -g

CFLAGS += -Wno-overlength-strings

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
