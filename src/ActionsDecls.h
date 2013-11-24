#ifndef ACTION_DECLS_H
#define ACTION_DECLS_H

/*
 * Capture program header definitions of input and output arguments.
 *
 * Arguments may be null if program contains errors.
 */
void doProgramDecl(char *prog_name, char *in_name, char *out_name);


/*
 * Perform actions necessary when exiting const decl part.
 */
void exitConstDeclPart(void);


/*
 * Create a new constant in the symbol table.
 * Extract the value and type information from the proxy.
 */
void doConstDecl(char *id, ProxySymbol *proxy);


/*
 * Perform actions necessary when exiting type decl part.
 */
void exitTypeDeclPart(void);


/*
 * Create a new type identifier symbol in the symbol table.
 *
 * Parameters:
 * 	id: name of symbol
 * 	type: Symbol with TYPE_KIND from which to copy the type
 *
 * Does not return
 */
void doTypeDecl(char *id, Symbol *type);


/*
 * Perform actions necessary when exiting variable dec section.
 */
void exitVarDeclPart(void);


/*
 * Declare a new variable with the given type.
 *
 * Return a pointer to type.
 */
Symbol *doVarDecl(char *id, Symbol *type);


/*
 * Exit a procedure or function definition.
 *
 * This is a good time to pop lexical level.
 */
void exitProcOrFuncDecl(void);


/*
 * Declare a new procedure with given arguments and perform anything
 * necessary when entering the procedure body definition (like increasing
 * the lexical level).
 *
 * Both arguments can be NULL if the definition contains errors.
 *
 * Return a pointer to the procedure.
 */
Symbol *enterProcDecl(char *id, struct ElementArray *ea);


/*
 * Declare a new function with the given arguments and perform anything
 * necessary when entering the function body definition.
 *
 * Both arguments can be NULL if the definition contains errors.
 * 
 * Return a pointer to the procedure.
 */
Symbol *enterFuncDecl(char *id, struct ElementArray *ea, Symbol *typeSym);


/*
 * Create a new parameter list from the given parameter.
 *
 * Return a pointer to the parameter list.
 */
struct ElementArray *createParmList(Symbol *parm);


/*
 * Append the given parameter to the parameter list.
 *
 * Return a poinnter to the parameter list.
 */
struct ElementArray *appendParmToParmList(
    struct ElementArray *ea, Symbol *parm);


/*
 * Create a new parameter with the given name and type.
 *
 * Return a pointer to the new parameter.
 */
Symbol *createNewParm(char *id, Symbol *type);


/*
 * Create a new var parm with the given name and type.
 *
 * Return a pointer to the new parameter.
 */
Symbol *createNewVarParm(char *id, Symbol *type);

#endif