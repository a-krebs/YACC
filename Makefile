################################################################################
# Makefile for Team YACC PAL compiler.
################################################################################

# Locations of all shared object files. Add .o files for each new module to
# this list.
OBJS=		$(BIN)/dummy_shared.o

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

# Compile command. Make's default rules don't seem to work with subdirectoreis
# so a command to invoke GCC is needed to all object files.
COMPILE= $(CC) $(CFLAGS) -c $< -o $@

# Build main executable
all: $(EXE)

# Build main executable with debug symbols and DEBUG option
debug: CFLAGS+= -g -DDEBUG
debug: $(EXE)

# Build test executable
test: CFLAGS+= -g
test: $(TESTEXE)

$(EXE): $(EXEOBJS)
	$(CC) -o $@ $+

$(TESTEXE): $(TESTOBJS)
	$(CC) -o $@ $+

$(BIN)/main.o: $(SRC)/main.c
	$(COMPILE)

$(BIN)/test.o: $(TEST)/test.c $(TEST)/minunit.h
	$(COMPILE)

$(BIN)/dummy_shared.o: $(SRC)/dummy_shared.c $(SRC)/dummy_shared.h
	$(COMPILE)

$(BIN)/test_dummy_shared.o: $(TEST)/test_dummy_shared.c $(TEST)/test_dummy_shared.h
	$(COMPILE)

clean:
	-rm -f $(BIN)/*.o $(TESTEXE) $(EXE)

