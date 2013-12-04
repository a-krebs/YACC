#ifndef ACTION_EXPRS_H
#define ACTION_EXPRS_H


/*
 * Perform assignment of x to y.
 */
void assignOp(ProxySymbol *x, ProxySymbol *y);


Symbol *variableAssignmentLookup(char *);
Symbol *recordFieldAssignmentLookup(ProxySymbol *, char *);
Symbol *pushArrayIndexValue(ProxySymbol *);
ProxySymbol *hashLookupToProxy(char *id);




/*
 * id1 == name of record, id3 == name of field we are trying to access
 */
ProxySymbol *recordAccessToProxy(ProxySymbol *p, char *id);


/*
 * Access an array given the list of indexes.
 *
 * Return a ProxySymbol of the expected type.
 */
ProxySymbol *arrayIndexAccess(ProxySymbol *var, ProxySymbol * indices);


/*
 * TODO: cannot use element array to construct list of proxy syms
 * as we are never explicitly constructing a list, just creating a bunch
 * of expressions which have to be proxy symbols.  How to do this this then?
 * Da Hack: link proxy symbols resulting from expressions through the
 * symbol's *next ptr!  
 */
/*
 * Concatenate two arrays of array indexes, maintaining order.
 *
 * Return a pointer to a concatenated list.
 */
ProxySymbol *concatArrayIndexList(ProxySymbol *list1, ProxySymbol *list2);


/*
 * Create a new array index list as a ProxySymbol.
 *
 * Return a pointer to the new list.
 */
ProxySymbol *createArrayIndexList(ProxySymbol *exp);


ProxySymbol *eqOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *notEqOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *lessOrEqOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *lessOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *gtOrEqOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *gtOp(ProxySymbol *x, ProxySymbol *y);
struct treeNode *unaryPlusOp(struct treeNode *y);
struct treeNode *unaryMinusOp(struct treeNode *y);
struct treeNode *plusOp(struct treeNode *x, struct treeNode *y);
struct treeNode *minusOp(struct treeNode *x, struct treeNode *y);
struct treeNode *orOp(struct treeNode *x, struct treeNode *y);
struct treeNode *multOp(struct treeNode *x, struct treeNode *y);
struct treeNode *divideOp(struct treeNode *x, struct treeNode *y);
struct treeNode *divOp(struct treeNode *x, struct treeNode *y);
struct treeNode *modOp(struct treeNode *x, struct treeNode *y);
struct treeNode *andOp(struct treeNode *x, struct treeNode *y);
struct treeNode *unaryNotOp(struct treeNode *y);
/*
 * perform calculation based on given opToken
 */
void constCalc(ProxySymbol *ps, ProxySymbol *x, int opToken, ProxySymbol *y);

double calcSum(ProxySymbol *x, ProxySymbol *y);
double calcSub(ProxySymbol *x, ProxySymbol *y);
double calcDivide(ProxySymbol *x, ProxySymbol *y);
int calcDiv(ProxySymbol *x, ProxySymbol *y);
double calcMult(ProxySymbol *x, ProxySymbol *y);
double calcMod(ProxySymbol *x, ProxySymbol *y);

int doAndOp(ProxySymbol *x, ProxySymbol *y);
int doOrOp(ProxySymbol *x, ProxySymbol *y);
/*
 * simple constant comparison functions are the following
 */
int doGtCmp(ProxySymbol *x, ProxySymbol *y);
int doGtOrEqCmp(ProxySymbol *x, ProxySymbol *y);
int doLessCmp(ProxySymbol *x, ProxySymbol *y);
int doLessOrEqCmp(ProxySymbol *x, ProxySymbol *y);
int doNotEqCmp(ProxySymbol *x, ProxySymbol *y);
int doEqCmp(ProxySymbol *x, ProxySymbol *y);
int doUnaryNotOp(ProxySymbol *y);
/*
 * three unary operation functions are the following
 */

double doUnaryPlusOp(ProxySymbol *y);
double doUnaryMinusOp(ProxySymbol *y);
/*
 * String comparison functions are the following
 */
int doStrEqCmp(ProxySymbol *x, ProxySymbol *y);
int doStrLessCmp(ProxySymbol *x, ProxySymbol *y);
int doStrGtCmp(ProxySymbol *x, ProxySymbol *y);




ProxySymbol *exprsOp(ProxySymbol *x, int opToken, ProxySymbol *y);

/*
 * Check that the given types are compatible when using the given
 * operator.
 *
 * Return a pointer to a Symbol struct 
 * that is populated with the resulting type when performing the operation, and
 * the value of the expression if it can be evaluated (like when dealing with
 * constants).
 *
 * If the types are not combatible for this operator, set error and return NULL.
 * TODO: right now success returns non-NULL for the benefit of unit tests.
 */
Symbol *assertOpCompat(
    Symbol *type1, int opToken, Symbol *type2);


/*
 * Return 0 if the given types are assignment compatible, otherwise return
 * non-zero
 */
int isAssignmentCompat(Symbol * type1, Symbol * type2);


#endif
