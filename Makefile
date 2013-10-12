################################################################################
# Makefile for Team YACC PAL compiler.
################################################################################

# Locations of all shared object files. Add .o files for each new module to
# this list.
OBJS=		$(BIN)/parser.tab.o 
OBJS+=		$(BIN)/lex.yy.o $(BIN)/Error.o $(BIN)/ErrorLL.o

# New variable for filtering out lex.yy.o and parser.tab.o from
# the compilation of the tests.
TOFILTER=	$(BIN)/lex.yy.o $(BIN)/parser.tab.o

# Root source directory
SRC=		src
# Directory to store compiled binaries
BIN=		bin
# Location of test source files
TEST=		test/unit

# Location and name of executables along with their object dependencies
EXE=		$(BIN)/pal
EXEOBJS=	$(BIN)/main.o $(OBJS)
TESTEXE=	$(BIN)/test
TESTOBJS1=	$(BIN)/test.o
TESTOBJS1+=	$(BIN)/testError.o $(BIN)/testErrorLL.o
TESTOBJS1+=	$(OBJS)
TESTOBJS=	$(filter-out $(TOFILTER), $(TESTOBJS1))


# Compiler flags for all builds
CFLAGS+= 

# Linked libraries for final build
LIBS=		-ll

# Compile command. Make's default rules don't seem to work with subdirectories
# so a command to invoke GCC is needed to all object files.
COMPILE= $(CC) $(CFLAGS) -c $< -o $@

#LEX and YACC/BISON compilation calls
LEXFLAGS=
LEX= lex $(LEXFLAGS) $<
YACCFLAGS= -d -y
YACC= bison $(YACCFLAGS) $< -o $@

# Build main executable
all: $(EXE)

# Build main executable with debug symbols and DEBUG option
debug: CFLAGS+= -g -DDEBUG
debug: $(EXE)

# Build test executable
test: CFLAGS+= -g -Isrc/
test: $(TESTEXE)

$(EXE): $(EXEOBJS)
	$(CC) -o $@ $+ $(LIBS)

$(TESTEXE): $(TESTOBJS)
	$(CC) -o $@ $+

$(BIN)/main.o: $(SRC)/main.c $(SRC)/parser.tab.c
	$(COMPILE)

$(BIN)/Error.o: $(SRC)/Error.c $(SRC)/Error.h
	$(COMPILE)

$(BIN)/testError.o: $(TEST)/testError.c $(TEST)/testError.h
	$(COMPILE)

$(BIN)/ErrorLL.o: $(SRC)/ErrorLL.c $(SRC)/ErrorLL.h
	$(COMPILE)

$(BIN)/testErrorLL.o: $(TEST)/testErrorLL.c $(TEST)/testErrorLL.h
	$(COMPILE)

$(BIN)/test.o: $(TEST)/test.c $(TEST)/minunit.h
	$(COMPILE)

$(BIN)/parser.tab.o: $(SRC)/parser.tab.c $(SRC)/lex.yy.c
	$(COMPILE)

$(BIN)/lex.yy.o: $(SRC)/lex.yy.c
	$(COMPILE)

$(SRC)/parser.tab.c: $(SRC)/parser.y
	$(YACC)

$(SRC)/lex.yy.c: $(SRC)/tokens.l
	$(LEX)
	mv lex.yy.c ./$(SRC)

clean:
	-rm -f $(BIN)/*.o $(TESTEXE) $(EXE) 
	-rm -f $(SRC)/lex.yy.c $(SRC)/parser.tab.h $(SRC)/parser.tab.c

build:
	make clean && make
