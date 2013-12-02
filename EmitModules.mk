
$(BIN)/EmitArithmetic.o: $(EMIT)/EmitArithmetic.c $(EMIT)/EmitArithmetic.h
	$(COMPILE)

$(BIN)/EmitExprs.o: $(EMIT)/EmitExprs.c $(EMIT)/EmitExprs.h
	$(COMPILE) 

$(BIN)/EmitDecls.o: $(EMIT)/EmitDecls.c $(EMIT)/EmitDecls.h
	$(COMPILE)

$(BIN)/EmitUtils.o: $(EMIT)/EmitUtils.c $(EMIT)/EmitUtils.h
	$(COMPILE)

$(BIN)/EmitStructStat.o: $(EMIT)/EmitStructStat.c $(EMIT)/EmitStructStat.h
	$(COMPILE)

$(BIN)/EmitProcs.o: $(EMIT)/EmitProcs.c $(EMIT)/EmitProcs.h
	$(COMPILE)	

$(BIN)/EmitRelational.o: $(EMIT)/EmitRelational.c $(EMIT)/EmitRelational.h
	$(COMPILE)

$(BIN)/EmitToFile.o: $(EMIT)/EmitToFile.c $(EMIT)/EmitToFile.h
	$(COMPILE)

$(BIN)/Emit.o: $(SRC)/Emit.c $(SRC)/Emit.h
	$(COMPILE)

