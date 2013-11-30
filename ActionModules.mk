$(BIN)/ActionsConsts.o: $(SRC)/ActionsConsts.c $(SRC)/ActionsConsts.h $(SRC)/parser.tab.c
	$(COMPILE)

$(BIN)/ActionsDecls.o: $(SRC)/ActionsDecls.c $(SRC)/ActionsDecls.h $(SRC)/parser.tab.c
	$(COMPILE)

$(BIN)/ActionsExprs.o: $(SRC)/ActionsExprs.c $(SRC)/ActionsExprs.h $(SRC)/parser.tab.c
	$(COMPILE)

$(BIN)/ActionsInvocs.o: $(SRC)/ActionsInvocs.c $(SRC)/ActionsInvocs.h $(SRC)/parser.tab.c
	$(COMPILE)

$(BIN)/ActionsStructStat.o: $(SRC)/ActionsStructStat.c $(SRC)/ActionsStructStat.h $(SRC)/parser.tab.c
	$(COMPILE)

$(BIN)/ActionsTypes.o: $(SRC)/ActionsTypes.c $(SRC)/ActionsTypes.h $(SRC)/parser.tab.c
	$(COMPILE)
