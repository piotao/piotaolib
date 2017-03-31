

# [c] piotao, 20170326, @hebron, 4piotaolib
# simple makefile to compile all programs

SOURCES = ${wildcard *.c}
OBJECTS = ${SOURCES:.c=.o}
DEPENDS = ${OBJECTS:.o=.d}
PROGRAM = ${SOURCES:.c=}
INCLUDE = -I/usr/include/SDL -I../src -I../SDL

LDFLAGS = -L../SDL -lm -lSDL -lSDL_image
CCFLAGS = -O2 -g -Wall -pedantic ${INCLUDE}

all: calcVariance getScanLine

calcVariance: calcVariance.c
	${CC} ${CCFLAGS} $< ../src/*.o -o $@ ${LDFLAGS}

getScanLine: getScanLine.c
	${CC} ${CCFLAGS} $< ../src/*.o -o $@ ${LDFLAGS}

%.d: %.c
	${CPP} ${CCFLAGS} $< -MM -MT ${@:.d=.o} >$@

%.o: %.c
	${CC} ${CCFLAGS} -c $< -o $@

clean:
	rm -f ${PROGRAM} ${OBJECTS} ${DEPENDS}

-include ${DEPENDS}

.PHONY: clean all


