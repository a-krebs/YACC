################################################################################
# Makefile for Team YACC PAL compiler.
################################################################################

# Locations of all shared object files. Add .o files for each new module to
# this list.
OBJS=		$(BIN)/dummy_shared.o $(BIN)/parser.tab.o 
OBJS+=		$(BIN)/lex.yy.o

# Root source directory
SRC=		src
# Directory to store compiled binaries
BIN=		bin
# Location of test source files
TEST=		test

# Location and name of executables along with their object dependencies
EXE=		$(BIN)/teamyacc
EXEOBJS=	$(BIN)/main.o $(OBJS)
TESTEXE=	$(BIN)/test
TESTOBJS=	$(BIN)/test.o $(BIN)/test_dummy_shared.o $(OBJS)

# Compiler flags for all builds
CFLAGS+= -Wall

# Linked libraries for all builds
LIBS=		-ll

# Compile command. Make's default rules don't seem to work with subdirectories
# so a command to invoke GCC is needed to all object files.
COMPILE= $(CC) $(CFLAGS) -c $< -o $@

#LEX and YACC/BISON compilation calls
LEX= lex $< 
YACC= bison -d -y  $< -o $@

# Build main executable
all: $(EXE)

# Build main executable with debug symbols and DEBUG option
debug: CFLAGS+= -g -DDEBUG
debug: $(EXE)

# Build test executable
test: CFLAGS+= -g
test: $(TESTEXE)

$(EXE): $(EXEOBJS)
	$(CC) -o $@ $+ $(LIBS)

$(TESTEXE): $(TESTOBJS)
	$(CC) -o $@ $+

$(BIN)/main.o: $(SRC)/main.c $(SRC)/parser.tab.c
	$(COMPILE)

$(BIN)/test.o: $(TEST)/test.c $(TEST)/minunit.h
	$(COMPILE)

$(BIN)/dummy_shared.o: $(SRC)/dummy_shared.c $(SRC)/dummy_shared.h
	$(COMPILE)

$(BIN)/parser.tab.o: $(SRC)/parser.tab.c $(SRC)/lex.yy.c
	$(COMPILE)

$(BIN)/lex.yy.o: $(SRC)/lex.yy.c
	$(COMPILE)

$(BIN)/test_dummy_shared.o: $(TEST)/test_dummy_shared.c $(TEST)/test_dummy_shared.h
	$(COMPILE)

$(SRC)/parser.tab.c: $(SRC)/parser.y
	$(YACC)

$(SRC)/lex.yy.c: $(SRC)/tokens.l
	$(LEX)
	mv lex.yy.c ./$(SRC)

clean:
	-rm -f $(BIN)/*.o $(TESTEXE) $(EXE) $(SRC)/lex.yy.c $(SRC)/parser.tab.h $(SRC)/parser.tab.c

