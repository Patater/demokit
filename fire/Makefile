LDFLAGS := -lSDL2
CFLAGS := -O3 -Werror -Wall -Wextra -pedantic -std=c90 -g
#CFLAGS := -O3 -Werror -Wall -Wextra -pedantic -std=c90

CFLAGS += $(shell sdl2-config --cflags)
LIBS += $(shell sdl2-config --libs)
CFLAGS += $(LIBS)

# CFLAGS += -Wno-switch
CFLAGS += -Wno-overlength-strings
CFLAGS += -fsanitize=undefined -fno-sanitize-recover=undefined

all: fire

run: fire
	./fire

OBJS := fire.c firepal.c
INC := firepal.h

fire: $(OBJS) $(INC)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-rm -f fire *.o
