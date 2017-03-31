
# [c] piotao, 20170326, @hebron, 4piotaolib
# simple makefile to blindly compile all modules

SOURCES = ${wildcard *.c}
OBJECTS = ${SOURCES:.c=.o}
DEPENDS = ${OBJECTS:.o=.d}
PROGRAM = ${patsubst %.c,%,${wildcard test*.c}}
INCLUDE = -I/usr/include/SDL -I../src -I../SDL

LDFLAGS = -lm -lSDL -lSDL_image -L../SDL
CCFLAGS = -O2 -g -Wall -pedantic ${INCLUDE}

all: ${PROGRAM}

test%: test%.o
	${CC} ${CCFLAGS} $+ ../src/*.o -o $@ ${LDFLAGS}

#-include ${DEPENDS}

#%.d: %.c
#	${CPP} ${CCFLAGS} $< -MM -MT ${@:.d=.o} >$@

%.o: %.c
	${CC} ${CCFLAGS} -c $< -o $@

clean:
	rm -f ${PROGRAM} ${OBJECTS} ${DEPENDS}

.PHONY: clean all


