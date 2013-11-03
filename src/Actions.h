struct Symbol *assertOpCompat(struct Symbol*, int, struct Symbol*);
int assignmentCompatEh(struct Symbol*, struct Symbol*);

void enterConstDeclPart(void);
void doConstDecl(void*, void*);
void enterTypeDeclPart(void);
void doTypeDecl(void*, void*);

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

void *anonIntLiteral(int);
void *anonRealLiteral(double);
void *anonStringLiteral(char*);
