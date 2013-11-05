#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Error.h"
#include "Hash.h"
#include "Type.h"
#include "Symbol.h"
#include "Utils.h"
#include "parser.tab.h"	/* token definitions used in operator compat checks */

extern struct hashElement *symbolTable[TABLE_SIZE];
extern int yylineno;
extern int colno;
/*
 * Utility functions. Can maybe be refactored into own module.
 */

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
 */
Symbol *assertOpCompat(
    Symbol *type1, int opToken, Symbol *type2) {

	type_t s1_t, s2_t;
	char *errMsg;	
	s1_t = getType(type1);
	s2_t = getType(type2);


	/* if type1 pointer is null but the operator is PLUS or MINUS (i.e.,
	 * it is a unary operator) then we assume the best */ 
	if ( (!type1) && (isUnaryOperator(opToken))) {
		if ((s2_t == REAL_T) || (s2_t == INTEGER_T)) return type2;
		return NULL; /* else error */
	} else return NULL; /* else it was an error */

	if (!areOpCompatible(type2, type2)) return NULL; /* errors recorded
							  * in called func */
	/*
	 * Now, we know type1 and type2 are op compatible (e.g., the exact
	 * same type, an int/real pair, or two strings with the same number
	 * of elements.   
	 */

	if (isRelationalOperator(opToken)) {
		if (!(isSimpleType(s1_t)) || !(isSimpleType(s2_t)) ||
		    (s1_t != STRING_T)) {
			/* non-simple, non-string types, relational
			 * operator cannot be applied */
			return NULL;
		}
		/* return pointer to predefined boolean type symbol */
		return NULL;
	}

	if (isLogicalOperator(opToken)) {
		/* Boolean operators work only on a pair of boolean types */
		if ((s1_t != BOOLEAN_T) || (s2_t != BOOLEAN_T)) return NULL;
		/* Else return pointer to pre-defined boolean type */
		return type1; 
	}

	if (s1_t == STRING_T) return NULL; /* not relational operator with
					    * string types => failure */
	/*
	 *  
 	 */ 
	if (s1_t == s2_t) return type1;

	switch (opToken) {
		case EQUAL:
			break;
		default:
			// TODO error
			break;
	}
	return NULL;
}

/*
 * Return 0 if the given types are assignment compatible, otherwise return
 * non-zero
 */
int isAssignmentCompat(Symbol type1, Symbol type2) {
	// TODO implement
	return -1;
}

/*
 * Parser action functions, in the order they appear in parser.y
 */

/*
 * Perform actions necessary when exiting const decl part.
 */
void exitConstDeclPart(void) {
	// function does nothing.
}

/*
 * Create a new constant in the symbol table.
 * Extract the value and type information from the proxy.
 */
void doConstDecl(char *id, ProxySymbol *proxy) {
	// TODO implementation.
}

/*
 * Perform actions necessary when exiting type decl part.
 */
void exitTypeDeclPart(void) {
	// probably nothing to do here
}

/*
 * Create a new type identifier symbol in the symbol table.
 */
void doTypeDecl(char *id, Symbol *type) {
	// TODO assign type to id
}

/*
 * Do a lookup in the symbol table for the type with the given id.
 *
 * Raise an error if the type is not available.
 *
 * Return a pointer to the type.
 */
Symbol *simpleTypeLookup(char *id) {
	return NULL;
}

/*
 * Add new_id as a mamber to scalar_list.
 *
 * Return scalar_list
 */
Symbol *appendToScalarListType(Symbol *scalar_list, char *new_id) {
	return scalar_list;
}

/*
 * Create a new scalar list type with id as the only member.
 *
 * Return a pointer to the new scalar list
 */
Symbol *createScalarListType(char *id) {
	return NULL;
}

/*
 * Create a new array type given the index type and base type.
 */
Symbol *createArrayType(Symbol *index, Symbol *base) {
	return NULL;
}

/*
 * Check that the given type is a valid array index type.
 *
 * Raise an error if the type is not valid as an index type.
 *
 * Return the given type.
 */
Symbol *assertArrIndexType(Symbol *index_type) {
	return index_type;
}

/*
 * Create a new subrange type. The arguments are proxy symbols that should
 * constain constant values for the range bounds.
 *
 * Return a pointer to the new subrange type.
 */
Symbol *createRangeType(ProxySymbol *lower, ProxySymbol *upper) {
	return NULL;
}

/*
 * Create a new record type from the given proxy. the proxy contains the name
 * of a field and the type of that field.
 *
 * Return a pointer to the new record type symbol.
 */
Symbol *createRecordType(ProxySymbol *first_field) {
	return NULL;
}

/*
 * Add a field to the given record type. The proxy new_field contains
 * the name and type of the new record field.
 *
 * Return a pointer to the record type.
 */
Symbol *appendFieldToRecordType(Symbol *record_type, ProxySymbol *new_field) {
	return record_type;
}

/*
 * Create a new ProxySymbol with the given id and type.
 *
 * Return a pointer to the new proxy.
 */
ProxySymbol *newRecordFieldProxy(char *id, Symbol *type) {
	return NULL;
}

/*
 * Perform actions necessary when exiting variable dec section.
 */
void exitVarDeclPart(void) {
	// nothing to do here
}

/*
 * Declare a new variable with the given type.
 *
 * Return a pointer to type.
 */
Symbol *doVarDecl(char *id, Symbol *type) {
	return type;
}

/*
 * Exit a procedure or function definition.
 *
 * This is a good time to pop lexical level.
 */
void exitProcOrFuncDecl(void) {
	// TODO
}

/*
 * Declare a new procedure with given arguments and perform anything
 * necessary when entering the procedure body definition (like increasing
 * the lexical level).
 *
 * Both arguments can be NULL if the definition contains errors.
 *
 * Return a pointer to the procedure.
 */
Symbol *enterProcDecl(char *id, ProxySymbol *argv) {
	return NULL;
}

/*
 * Declare a new function with the given arguments and perform anything
 * necessary when entering the function body definition.
 *
 * Both arguments can be NULL if the definition contains errors.
 * 
 * Return a pointer to the procedure.
 */
Symbol *enterFuncDecl(char *id, ProxySymbol *argv) {
	return NULL;
}

/*
 * Create a new parameter list from the given parameter.
 *
 * Return a pointer to the parameter list.
 */
ProxySymbol *createParmList(ProxySymbol *parm) {
	return NULL;
}

/*
 * Append the given parameter to the parameter list.
 *
 * Return a poinnter to the parameter list.
 */
ProxySymbol *appendParmToParmList(
    ProxySymbol *parm_list, ProxySymbol *new_parm) {
	return parm_list;
}

/*
 * Create a new parameter with the given name and type.
 *
 * Return a pointer to the new parameter.
 */
ProxySymbol *createNewParm(char *id, Symbol *type) {
	return NULL;
}

/*
 * Create a new var parm with the given name and type.
 *
 * Return a pointer to the new parameter.
 */
ProxySymbol *createNewVarParm(char *id, Symbol *type) {
	return NULL;
}

/*
 * Perform assignment of x to y.
 */
void assignOp(ProxySymbol *x, ProxySymbol *y) {
}

ProxySymbol *hashLookupToProxy(char *id) {
	return NULL;
}

ProxySymbol *recordAccessToProxy(char *id1, char *id3) {
	return NULL;
}

ProxySymbol *eqOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *notEqOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *lessOrEqOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *lessOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *gtOrEqOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *gtOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *unaryPlusOp(ProxySymbol *y) {
	return NULL;
}

ProxySymbol *unaryMinusOp(ProxySymbol *y) {
	return NULL;
}

ProxySymbol *plusOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *minusOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *orOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *multOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *divideOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *divOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *modOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *andOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *getProxyFromSymbol(Symbol *symbol) {
	return NULL;
}

ProxySymbol *unaryNotOp(ProxySymbol *x) {
	return NULL;
}

/*
 * Make a new anonymous symbol with type integer and given value.
 * Return pointer to the hash symbol.
 */
// TODO change return type
void *anonIntLiteral(int value) {
	// TODO implement
	return NULL;
}
	
/*
 * Make a new anonymous symbol with type real and given value.
 * Return a pointer to the hash symbol.
 */
// TODO change return type
void *anonRealLiteral(double value) {
	// TODO implement
	return NULL;
}

/*
 * Make a new anonymous symbol with the given string.
 * Return a pointer to the hash symbol.
 */
// TODO change return type
void *anonStringLiteral(char *value) {
	// TODO implment
	return NULL;
}
