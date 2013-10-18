YACC - Yet Another CMPUT 415 Compiler
====

CMPUT 415 Compiler Project

Installation
----

To build, use `make`. The `pal` executable with be located at `bin/pal`.

To build the unit testing executable, use `make test`, which will produce
the test executable at `bin/test`.
To build the lexical tester, use `make lextest`, which will build
`bin/lextest`. This binary prints the tokens, in the order the lexer reads them,
to standard output.

There is also a debug build, `make debug`, which enables VERY verbose debugging
ouput.

To run the entire suite of tests, use `make integration_tests` and
`make unit_tests`.

Usage
----

Please refer to the man page for usage. Try `nroff -man pal.man | less`.
