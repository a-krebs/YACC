$(BIN)/PreDefAsc.o: $(SRC)/PreDefAsc.c $(SRC)/PreDefAsc.h
	$(COMPILE)

$(ASC)/__PreDefAsc.__asc: $(ASC)/*.asc
	ls $(ASC)/*.asc | xargs -n 1 cat > $@

$(ASC)/__PreDefAsc.__c: $(ASC)/__PreDefAsc.__asc
	cat $< | sed -e 's/"/\\"/g' -e "s/\t/\\\t/g" -e \
		"s/\(.*\)/emitStr(\&stmts, \"\", \"\1\", \"\\\n\");/g" > $@

$(SRC)/PreDefAsc.c: $(ASC)/PreDefAsc.template.c $(ASC)/__PreDefAsc.__c
	sed -e "/<-- MAKE PLACES EMIT STATEMENTS HERE -->/r\
		$(ASC)/__PreDefAsc.__c" -e "s///" $< > $@
