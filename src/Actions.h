#include "Symbol.h"

Symbol *assertOpCompat(Symbol*, int, Symbol*);
int isAassignmentCompat(Symbol*, Symbol*);

/* declaration lists */
void exitConstDeclPart(void);
void doConstDecl(char*, ProxySymbol*);
void exitTypeDeclPart(void);
void doTypeDecl(char*, Symbol*);

/* types */
Symbol *simpleTypeLookup(char*);
Symbol *appendToScalarListType(Symbol*, char*);
Symbol *createScalarListType(char*);
Symbol *createArrayType(Symbol*, Symbol*);
Symbol *assertArrIndexType(Symbol*);
Symbol *createRangeType(ProxySymbol*, ProxySymbol*);
Symbol *createRecordType(ProxySymbol*);
Symbol *appendFieldToRecordType(ProxySymbol*, ProxySymbol*);
ProxySymbol *newRecordFieldProxy(char*, Symbol*);

/* var decl list */
void exitVarDeclPart(void);
Symbol *doVarDecl(char*, Symbol*);

/* proc and function decls */
Symbol *doVarDecl(char*, Symbol*);
void exitProcOrFuncDecl(void);
Symbol *enterProcDecl(char*, ProxySymbol*);
Symbol *enterFuncDecl(char*, ProxySymbol*);
ProxySymbol *createParmList(ProxySymbol*);
ProxySymbol *appendParmToParmList(ProxySymbol*, ProxySymbol*);
ProxySymbol *createNewParm(char*, Symbol*);
ProxySymbol *createNewVarParm(char*, Symbol*);

/* expressions and operators */
ProxySymbol *assignOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *hashLookupToProxy(char*);
ProxySymbol *recordAccessToProxy(char*, char*);
ProxySymbol *eqOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *notEqOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *lessOrEqOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *lessOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *gtOrEqOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *gtOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *unaryPlusOp(ProxySymbol*);
ProxySymbol *unaryMinusOp(ProxySymbol*);
ProxySymbol *plusOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *minusOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *orOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *multOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *divideOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *divOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *modOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *andOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *getProxyFromSymbol(ProxySymbol *symbol);
ProxySymbol *unaryNotOp(ProxySymbol*);

/* constants */
void *anonIntLiteral(int);
void *anonRealLiteral(double);
void *anonStringLiteral(char*);
