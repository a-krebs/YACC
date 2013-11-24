################################################################################
# Makefile for Team YACC PAL compiler.
################################################################################

# Locations of all shared object files. Add .o files for each new module to
# this list.
OBJS=		$(BIN)/parser.tab.o 
OBJS+=		$(BIN)/lex.yy.o $(BIN)/Error.o $(BIN)/ErrorLL.o
OBJS+=		$(BIN)/ProgList.o $(BIN)/ElementArray.o 
OBJS+=		$(BIN)/Type.o $(BIN)/Kind.o $(BIN)/Utils.o $(BIN)/Emit.o
OBJS+=		$(BIN)/Actions.o
OBJS+=		$(BIN)/Hash.o
OBJS+=		$(BIN)/PreDef.o
OBJS+=		$(BIN)/Init.o
OBJS+=		$(BIN)/Symbol.o $(BIN)/SymbolAPI.o $(BIN)/SymbolArray.o 
OBJS+=		$(BIN)/SymbolInvoc.o  $(BIN)/SymbolPrivateAPI.o 
OBJS+=		$(BIN)/SymbolProxy.o

# New variable for filtering out lex.yy.o and parser.tab.o from
# the compilation of the tests.
TEST_FILTER=	$(BIN)/lex.yy.o $(BIN)/parser.tab.o #$(BIN)/Utils.o
#TEST_FILTER+=	$(BIN)/Actions.o
LEX_FILTER=	$(BIN)/parser.tab.o

# Root source directory
SRC=		src
# Directory to store compiled binaries
BIN=		bin
# Location of test source files
TEST=		test/unit
TEST_FILES=	test/integration

# Location and name of executables along with their object dependencies
EXE=		$(BIN)/pal
EXEOBJS=	$(BIN)/main.o $(OBJS)

LEXTEST_EXE=	$(BIN)/lextest
LEXTEST_OBJS1=	$(BIN)/lextest.o $(BIN)/tokenTestParser.tab.o $(OBJS)
LEXTEST_OBJS=	$(filter-out $(LEX_FILTER), $(LEXTEST_OBJS1))


TESTEXE=	$(BIN)/test
TESTOBJS1=	$(BIN)/test.o
TESTOBJS1+=	$(BIN)/testHash.o
TESTOBJS1+=	$(BIN)/testError.o $(BIN)/testErrorLL.o $(BIN)/testProgList.o
TESTOBJS1+=	$(BIN)/testType.o $(BIN)/testSymbol.o $(BIN)/testElementArray.o
TESTOBJS1+=	$(BIN)/testActions.o $(BIN)/testUtils.o $(BIN)/testKind.o
TESTOBJS1+=	$(BIN)/testingUtils.o
TESTOBJS1+=	$(BIN)/testPreDef.o $(BIN)/testPreDefAsc.o
TESTOBJS1+=	$(OBJS)
TESTOBJS=	$(filter-out $(TEST_FILTER), $(TESTOBJS1))



# for debug output, location of Bison/YACC report
BISONREPORT= 	bisonReport.out

# Compiler flags for all builds
CFLAGS+=	-Wall -std=c99
# exclude these flags from compiles involving Bison/Flex
FLEXBISONFLAGEXCLUDES= -Wall -std=c99

# Linked libraries for final build
LIBS=		-ll

# Compile command. Make's default rules don't seem to work with subdirectories
# so a command to invoke GCC is needed to all object files.
COMPILE= $(CC) $(CFLAGS) -c $< -o $@
# Use this command for anything that includes Bison/Flex. The warnings
# from implicin includes when using Bison/Flex can't really be avoided.
BISONFLEXCOMPILE = $(CC) $(filter-out $(FLEXBISONFLAGEXCLUDES), $(CFLAGS))\
		       -c $< -o $@

# LEX and YACC/BISON compilation calls
LEXFLAGS=
LEX= lex $(LEXFLAGS) $<
YACCFLAGS= -d -y
YACC= bison $(YACCFLAGS) $< -o $@

# sed command to include token definitions in parser files
SED_INCLUDE= 	sed -e "/<-- MAKE PLACES DEFINITIONS.TOKENS FILE HERE -->/r\
		    $(SRC)/definitions.tokens" -e "s///" $< > $@

# Build main executable
all: $(EXE)

# Build main executable with debug symbols and DEBUG option
debug: CFLAGS+= -g
debug: YACCFLAGS += --report-file=$(BISONREPORT) -v
debug: $(EXE)

debug_verbose: CFLAGS+= -g -DDEBUG -DYYDEBUG=1
debug_verbose: YACCFLAGS += --report-file=$(BISONREPORT) -v
debug_verbose: $(EXE)

debug_hash: CFLAGS+= -g -DHASHDEBUG
debug_hash: YACCFLAGS += --report-file=$(BISONREPORT) -v
debug_hash: $(EXE)

# Build main using tokenTestParser.y to analyze lexical tokens
lextest: CFLAGS+= -g -DLEXTEST_DEBUG
lextest: $(LEXTEST_EXE)

# Build test executable
test: CFLAGS+= -g -Isrc/ -DTESTBUILD -D_POSIX_C_SOURCE=200809L
test: $(TESTEXE)

$(EXE): $(EXEOBJS)
	$(CC) -o $@ $+ $(LIBS)

$(TESTEXE): $(TESTOBJS)
	$(CC) -o $@ $+

$(LEXTEST_EXE): $(LEXTEST_OBJS)
	$(CC) -o $@ $+ $(LIBS)

$(BIN)/main.o: $(SRC)/main.c $(SRC)/parser.tab.c $(SRC)/args.h
	$(BISONFLEXCOMPILE)

$(BIN)/lextest.o: $(SRC)/main.c $(SRC)/tokenTestParser.tab.c
	$(BISONFLEXCOMPILE)

$(SRC)/Definitions.h:
	#Do nothing

$(BIN)/Error.o: $(SRC)/Error.c $(SRC)/Error.h
	$(COMPILE)

$(BIN)/Kind.o: $(SRC)/Kind.c $(SRC)/Kind.h $(SRC)/Definitions.h
	$(COMPILE)

$(BIN)/Utils.o: $(SRC)/Utils.c $(SRC)/Utils.h $(SRC)/parser.tab.c
	$(COMPILE)

$(BIN)/ElementArray.o: $(SRC)/ElementArray.c $(SRC)/ElementArray.h
	$(COMPILE)

$(BIN)/Emit.o: $(SRC)/Emit.c $(SRC)/Emit.h
	$(COMPILE)

$(BIN)/ProgList.o: $(SRC)/ProgList.c $(SRC)/ProgList.h
	$(COMPILE)

include SymbolModules.mk

$(BIN)/Type.o: $(SRC)/Type.c $(SRC)/Type.h $(SRC)/Definitions.h
	$(COMPILE)

$(BIN)/ErrorLL.o: $(SRC)/ErrorLL.c $(SRC)/ErrorLL.h
	$(COMPILE)

$(BIN)/Hash.o: $(SRC)/Hash.c $(SRC)/Hash.h
	$(COMPILE)	

$(BIN)/Actions.o: $(SRC)/Actions.c $(SRC)/Actions.h $(SRC)/parser.tab.c
	$(COMPILE)

$(BIN)/PreDef.o: $(SRC)/PreDef.c $(SRC)/PreDef.h $(SRC)/Definitions.h
	$(COMPILE)	

$(BIN)/Init.o: $(SRC)/Init.c $(SRC)/Init.h 
	$(COMPILE)		

$(BIN)/testSymbol.o: $(TEST)/testSymbol.c $(TEST)/testSymbol.h
	$(COMPILE)

$(BIN)/testProgList.o: $(TEST)/testProgList.c $(TEST)/testProgList.h
	$(COMPILE)

$(BIN)/testError.o: $(TEST)/testError.c $(TEST)/minunit.h
	$(COMPILE)

$(BIN)/testErrorLL.o: $(TEST)/testErrorLL.c $(TEST)/testErrorLL.h
	$(COMPILE)

$(BIN)/testElementArray.o: $(TEST)/testElementArray.c $(TEST)/testElementArray.h
	$(COMPILE)

$(BIN)/testType.o: $(TEST)/testType.c $(TEST)/testType.h
	$(COMPILE)

$(BIN)/testKind.o: $(TEST)/testKind.c $(TEST)/testKind.h
	$(COMPILE)

$(BIN)/testUtils.o: $(TEST)/testUtils.c $(TEST)/testUtils.h
	$(COMPILE)

$(BIN)/test.o: $(TEST)/test.c $(TEST)/minunit.h
	$(COMPILE)

$(BIN)/testHash.o: $(TEST)/testHash.c $(TEST)/testHash.h
	$(COMPILE)		

$(BIN)/testActions.o: $(TEST)/testActions.c $(TEST)/testActions.h
	$(COMPILE)

$(BIN)/testingUtils.o: $(TEST)/testingUtils.c $(TEST)/testingUtils.h $(SRC)/Definitions.h
	$(COMPILE)

$(BIN)/testPreDef.o: $(TEST)/testPreDef.c $(TEST)/testPreDef.h
	$(COMPILE)

$(BIN)/testPreDefAsc.o: $(TEST)/testPreDefAsc.c $(TEST)/testPreDefAsc.h
	$(COMPILE)

$(BIN)/parser.tab.o: $(SRC)/parser.tab.c $(SRC)/lex.yy.c
	$(BISONFLEXCOMPILE)

$(BIN)/tokenTestParser.tab.o: $(SRC)/tokenTestParser.tab.c $(SRC)/lex.yy.c
	$(BISONFLEXCOMPILE)

$(SRC)/tokenTestParser.tab.c: $(SRC)/generated_tokenTestParser.y
	$(YACC)

$(BIN)/lex.yy.o: $(SRC)/lex.yy.c
	$(BISONFLEXCOMPILE)

$(SRC)/parser.tab.c: $(SRC)/generated_parser.y
	$(YACC)

$(SRC)/lex.yy.c: $(SRC)/tokens.l
	$(LEX)
	mv lex.yy.c ./$(SRC)

$(SRC)/generated_parser.y: $(SRC)/parser.y $(SRC)/definitions.tokens $(SRC)/args.h
	$(SED_INCLUDE)

$(SRC)/generated_tokenTestParser.y: $(SRC)/tokenTestParser.y $(SRC)/definitions.tokens $(SRC)/args.h
	$(SED_INCLUDE)

clean:
	-rm -f $(BIN)/*.o core $(LEXTEST_EXE) $(TESTEXE) $(EXE) 
	-rm -f $(SRC)/lex.yy.c $(SRC)/parser.tab.h
	-rm -f $(SRC)/parser.tab.c $(SRC)/tokenTestParser.tab.h
	-rm -f $(SRC)/tokenTestParser.tab.c
	-rm -f $(BISONREPORT)
	-rm -f $(SRC)/generated_parser.y
	-rm -f $(SRC)/generated_tokenTestParser.y
	-rm -f $(TEST)/ProgListTestFile.txt
	-rm -f $(TEST)/ProgListTestFileOut.lst
	-rm -f 0.pal 1.pal 2.pal 3.pal 4.pal
	-rm -f 5.pal 6.pal 7.pal 8.pal 9.pal

# shortcuts for common actions
build:
	make clean && make

unit_tests:
	make clean && make test
	./bin/test

integration_tests_base:
	@make -s build
	@mv $(EXE) $(EXE).bak
	@make -s clean
	@make -s lextest
	@mv $(LEXTEST_EXE) $(LEXTEST_EXE).bak
	@make -s clean
	@mv $(EXE).bak $(EXE)
	@mv $(LEXTEST_EXE).bak $(LEXTEST_EXE)


# @ symbols supress printing commands that are executed
# -s flag on make suppressess all output from make
integration_tests:
	@make -s integration_tests_base
	@make -s syntax_tests_
	@make -s semantic_tests_
	@make -s full_tests_

syntax_tests:
	@make -s integration_tests_base
	@make -s syntax_tests_

syntax_tests_:
	@echo "SYNTAX TESTS:"
	@-cd test && python testRunner.py -x -d ./integration/syntax

semantic_tests:
	@make -s integration_tests_base
	@make -s semantic_tests_

semantic_tests_:
	@echo "CHECKING SEMANTIC TESTS FOR SYNTAX ERRORS:"
	@-cd test && python testRunner.py -x -i -d ./integration/semantic
	@echo "\nSEMANTIC TESTS:"
	@-cd test && python testRunner.py -c -d ./integration/semantic

asc_tests:
	@make -s integration_tests_base
	@make -s asc_tests_

asc_tests_:
	@echo "ASC TESTS:"
	@-cd test && python testRunner.py -a -d ./integration/asc

full_tests:
	@make -s integration_tests_base
	@make -s full_tests_
	
full_tests_:
	@echo "\nFULL TESTS:"
	@-cd test && python testRunner.py -d ./integration/full

# remove all .lst files
clean_lst:
	find . -name "*.lst" -delete

include Checkpoint2.mk
