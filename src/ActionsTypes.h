#ifndef ACTION_TYPES_H
#define ACTION_TYPES_H

/*
 * Do a lookup in the symbol table for the type with the given id.
 *
 * Raise an error if the type is not available.
 *
 * Return a pointer to the type.
 */
Symbol *simpleTypeLookup(char *id);


/*
 * Add new_id as a mamber to sclalar_list.
 *
 * Return scalar_list
 */
struct ElementArray *appendToScalarListType(struct ElementArray *ea,
    char *id);


/*
 * Create a new list of scalars (later used in constructing a scalar list type).
 * The list will contain a single constant named by the given id
 *
 * Parameters:
 * 	id: the name of the scalar to add to the new list
 *
 * Return:
 * 	A pointer to an ElementArray struct representing the list of scalars.
 *		The given id will be the only member.
 *	NULL if id is already defined in scope.
 */
struct ElementArray * createScalarList(char *id);


/*
 * Create a new scalar list type with ea as the scalars in the list
 *
 * Parameters:
 * 	ea: an ElementArray of the scalars that should be in the list
 * Return:
 * 	a pointer to the new scalar list or NULL if ea is NULL
 */
Symbol *createScalarListType(struct ElementArray *ea);


/*
 * Create a new array type given the index type and base type.
 *
 * Parameters:
 * 	index: symbol for index type of kind TYPE_KIND
 * 	base: symbol for base type of kind TYPE_KIND
 *
 * Return:
 * 	new symbol of kind TYPE_KIND
 * 	
 */
Symbol *createArrayType(Symbol *index, Symbol *base);


/*
 * Check that the given type is a valid array index type.
 *
 * Raise an error if the type is not valid as an index type.
 *
 * Return the given type.
 */
Symbol *assertArrIndexType(Symbol *index_type);


/*
 * Create a new subrange type. The arguments are proxy symbols that should
 * constain constant values for the range bounds.
 *
 * Return a pointer to the new subrange type.
 */
Symbol *createRangeType(ProxySymbol *lower, ProxySymbol *upper);


/*
 * Create a new record type from the array of fields.
 *
 * Return a pointer to the new record type symbol.
 */
Symbol *createRecordType(struct ElementArray *fields);


/*
 * Create a new element array from the given proxy symbol.
 *
 * Return a pointer to the new array.
 */
struct ElementArray *createRecordMemberList(ProxySymbol *field);


/*
 * Append the given proxySymbol to the array of fields.
 *
 * Return a pointer to the array.
 */
struct ElementArray *appendToRecordMemberList(
    struct ElementArray *array, ProxySymbol *field);


/*
 * Create a new ProxySymbol with the given id and type.
 *
 * Return a pointer to the new proxy.
 */
ProxySymbol *newRecordFieldProxy(char *id, Symbol *type) ;

#endif