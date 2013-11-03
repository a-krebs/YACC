struct Symbol *assertOpCompat(struct Symbol*, int, struct Symbol*);
int assignmentCompatEh(struct Symbol*, struct Symbol*);

/* declaration list parts */
void exitConstDeclPart(void);
void doConstDecl(char*, struct Symbol*);
void exitTypeDeclPart(void);
void doTypeDecl(char*, struct Symbol*);

/* type parts */
struct Symbol *simpleTypeLookup(char*);
struct Symbol *appendToScalarList(struct Symbol*, char*);
struct Symbol *createScalarList(char*);

/* expressions and operators */
struct Symbol *assignOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *hashLookupToTmp(char *id);
struct Symbol *recordAccessToTmp(char *id1, char *id3);
struct Symbol *eqOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *notEqOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *lessOrEqOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *lessOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *gtOrEqOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *gtOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *unaryPlusOp(struct Symbol *tmp2);
struct Symbol *unaryMinusOp(struct Symbol *tmp2);
struct Symbol *plusOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *minusOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *orOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *multOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *divideOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *divOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *modOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *andOp(struct Symbol *tmp1, struct Symbol *tmp3);
struct Symbol *getTmpFromSymbol(struct Symbol *symbol);
struct Symbol *unaryNotOp(struct Symbol *tmp2);

/* constants */
void *anonIntLiteral(int);
void *anonRealLiteral(double);
void *anonStringLiteral(char*);
