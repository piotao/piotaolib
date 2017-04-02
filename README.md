# piotaolib



ABOUT:
------------------------------------------------------
This is a library for some simple, common and sometimes boring programmatic stuff. Just plain C-code, no fancy optimizations,
and some untested stuff.

The whole thing is split into parts:

./src
The main library: modules are connected thru common data types, etc. The base data type is 'Data', which is by default typedefed to double.

./tests
Some simple rudimentary programs for testing, if stuff from modules is working.

./utils
Programs I wrote which use the library for some production stuff, calculations (mostly), or data processing.



HOW TO COMPILE:
------------------------------------------------------
Usually, running make is just enough, but on some systems there may be an exotic configuration, so errors or warnings may occur.
There are also prerequisities, like SDL library.
So, install SDL library and SDL header files appropriate to your distribution.

Compile with make, the command is:

	make

or:

	make all

There is also Makefile in each directory, you can invoke make in each of them spearately.



HOW TO CLEAN:
------------------------------------------------------
Run make with clean:

	make clean



AUTHOR:
-------------------------------------------------------
Piotr Arłukowicz, <piotao@inf.ug.edu.pl>, [piotao]
GITHUB: https://github.com/piotao/piotaolib


