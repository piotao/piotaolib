
# [c] piotao, 20170326, @hebron, 4piotaolib
# simple makefile to blindly compile all modules

SOURCES = ${wildcard *.c}
HEADERS = ${SOURCES:.c=.h}
OBJECTS = ${SOURCES:.c=.o}
DEPENDS = ${OBJECTS:.o=.d}
INCLUDE = -I/usr/include/SDL -I../SDL

LDFLAGS = -lm -lSDL -lSDL_image -L../SDL
CCFLAGS = -O2 -g -Wall -pedantic ${INCLUDE}

all: ${OBJECTS}

-include ${DEPENDS}

%.d: %.c
	${CPP} ${CCFLAGS} $< -MM -MT ${@:.d=.o} >$@

%.o: %.c
	${CC} ${CCFLAGS} -c $< -o $@

clean:
	rm -f ${OBJECTS} ${DEPENDS}

.PHONY: clean all


