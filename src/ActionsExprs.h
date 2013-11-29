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
ProxySymbol *unaryPlusOp(ProxySymbol *y);
ProxySymbol *unaryMinusOp(ProxySymbol *y);
ProxySymbol *plusOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *minusOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *orOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *multOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *divideOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *divOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *modOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *andOp(ProxySymbol *x, ProxySymbol *y);
ProxySymbol *unaryNotOp(ProxySymbol *y);

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
