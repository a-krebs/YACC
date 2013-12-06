$(BIN)/Symbol.o: $(SRC)/Symbol.c $(SRC)/Symbol.h $(SRC)/Definitions.h
	$(COMPILE)	

$(BIN)/SymbolAPI.o: $(SRC)/SymbolAPI.c $(SRC)/SymbolAPI.h $(SRC)/Definitions.h
	$(COMPILE)	

$(BIN)/SymbolArray.o: $(SRC)/SymbolArray.c $(SRC)/SymbolArray.h $(SRC)/Definitions.h
	$(COMPILE)	

$(BIN)/SymbolInvoc.o: $(SRC)/SymbolInvoc.c $(SRC)/SymbolInvoc.h $(SRC)/Definitions.h
	$(COMPILE)	

$(BIN)/SymbolPrivateAPI.o: $(SRC)/SymbolPrivateAPI.c $(SRC)/SymbolPrivateAPI.h $(SRC)/Definitions.h
	$(COMPILE)	

$(BIN)/SymbolProxy.o: $(SRC)/SymbolProxy.c $(SRC)/SymbolProxy.h $(SRC)/Definitions.h
	$(COMPILE)				
