CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

INCLUDES = -I./include

SRCS = \
	   src/main.cc \
	   src/game.cc

OBJS = $(SRCS:.cc=.o)

MAIN = game

.PHONY: depend clean

all: $(MAIN)
	@echo Game has been built.

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LDFLAGS)

.cc.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) src/*.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
