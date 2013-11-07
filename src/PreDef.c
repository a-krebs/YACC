#include "PreDef.h"

Symbol *getPreDefBool(struct preDefTypeSymbols *preDefTypeSymbols) {
	return preDefTypeSymbols->boolean;
}


Symbol *getPreDefChar(struct preDefTypeSymbols *preDefTypeSymbols) {
	return preDefTypeSymbols->chars;
}


Symbol *getPreDefInt(struct preDefTypeSymbols *preDefTypeSymbols) {
	return preDefTypeSymbols->integer;
}


Symbol *getPreDefReal(struct preDefTypeSymbols *preDefTypeSymbols) {
	return preDefTypeSymbols->real;
}
