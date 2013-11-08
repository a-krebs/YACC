#include "Symbol.h"

Symbol *assertOpCompat(Symbol*, int, Symbol*);
int isAassignmentCompat(Symbol*, Symbol*);

/* program header */
void doProgramDecl(char*, char*, char*);

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
Symbol *createRecordType(struct ElementArray*);
struct ElementArray *createRecordMemberList(ProxySymbol*);
struct ElementArray *appendToRecordMemberList(
    struct ElementArray*, ProxySymbol*);
ProxySymbol *newRecordFieldProxy(char*, Symbol*);

/* var decl list */
void exitVarDeclPart(void);
Symbol *doVarDecl(char*, Symbol*);

/* proc and function decls */
Symbol *doVarDecl(char*, Symbol*);
void exitProcOrFuncDecl(void);
Symbol *enterProcDecl(char*, struct ElementArray *);
Symbol *enterFuncDecl(char*, struct ElementArray *, Symbol *);
struct ElementArray *createParmList(Symbol*);
struct ElementArray *appendParmToParmList(struct ElementArray*, Symbol*);
Symbol *createNewParm(char*, Symbol*);
Symbol *createNewVarParm(char*, Symbol*);

/* expressions and operators */
ProxySymbol *assignOp(ProxySymbol*, ProxySymbol*);
ProxySymbol *hashLookupToProxy(char*);
ProxySymbol *recordAccessToProxy(char*, char*);
ProxySymbol *arrayIndexAccess(ProxySymbol*, ProxySymbol*);
ProxySymbol *concatArrayIndexList(ProxySymbol*, ProxySymbol*);
ProxySymbol *createArrayIndexList(ProxySymbol*);
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
ProxySymbol *unaryNotOp(ProxySymbol*);

/* constants */
ProxySymbol *proxyIntLiteral(int);
ProxySymbol *proxyRealLiteral(double);
ProxySymbol *proxyStringLiteral(char*);

/* procedure and function invokations */
void prodInvok(char*, struct ElementArray*);
ProxySymbol *funcInvok(char*, struct ElementArray*);
struct ElementArray *createArgList(Symbol*);
struct ElementArray *concatArgLists(struct ElementArray*, struct ElementArray*);

/* loop control */
void continueLoop(void);
void exitLoop(void);
void endWhileLoop(void);
