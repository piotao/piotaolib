
# [c] piotao, 20170326, @hebron, piotaolib library
# this Makefile aims to compile all components from the library
# but partial compilation of specific dirs should be also possible
# Licence: GPL 3.0
# -

DIRS = src tests utils

all:
	make -C src -f Makefile
	make -C tests -f Makefile
	make -C utils -f Makefile

clean:
	make -C src -f Makefile clean
	make -C tests -f Makefile clean
	make -C utils -f Makefile clean

.PHONY: all clean ${DIRS}

#defs.o: defs.c defs.h
#data.o: data.c data.h defs.h listc.h
#gpu.o: gpu.c gpu.h
#listc.o: listc.c defs.h listc.h
#listd.o: listd.c listd.h defs.h
#matrix.o: matrix.c defs.h matrix.h vector.h data.h
#maxmin.o: maxmin.c defs.h data.h maxmin.h
#norm.o: norm.c defs.h norm.h listd.h
#options.o: options.c options.h
#pixels.o: pixels.c  data.h defs.h listd.h pixels.h vector.h matrix.h
#stack.o: stack.c defs.h data.h stack.h
#timers.o: timers.c timers.h defs.h
#variance.o: variance.c defs.h data.h vector.h matrix.h average.h listd.h
#vector.o: vector.c defs.h data.h listc.h vector.h
#average.o: average.c defs.h data.h listd.h matrix.h vector.h average.h

#FULLDIRS = ${wildcard modules/*.c}
#FULLTEST = ${wildcard tests/test*.c}
#MODULES  = ${patsubst modules/%,%,${FULLDIRS}}
#TESTPROG = ${patsubst tests/%,%,${FULLTEST}}
#OBJECTS  = ${MODULES:.c=.o}
#DEPENDS  = ${OBJECTS:.o=.d}
#
#all: mods
#	@echo FULLDIRS: ${FULLDIRS}
#	@echo FULLTEST: ${FULLTEST}
#	@echo MODULES: ${MODULES}
#	@echo TESTPROG: ${TESTPROG}
#
#mods: ${MODULES}
#	@echo ${MODULES}
#
#%.d: %.c
#	${CPP} $< -MM -MT ${@:.d=.o} >$@
#
#%.o: %.c
#	${CC} -c $< -o $@
#


