#ifndef ACTION_INVOCS_H
#define ACTION_INVOCS_H

#include "Tree.h"

/*
 * Invoke procedure with given name.
 *
 * The argument argv contains a list of arguments.
 */
void procInvok(char *id, struct ElementArray *ea);


/*
 * Invoke function with the given name.
 *
 * The argument argv contains a list of arguments.
 *
 * Return a ProxySymbol containing the type returned.
 */
struct treeNode *funcInvok(char *id, struct ElementArray *argv);


/*
 * Create an argument list for function and procedure invocation.
 *
 * Return a pointer to a ProxySymbol containing the list.
 */
struct ElementArray *createArgList(struct treeNode *arg);


/*
 * Concatenate two lists of arguments, maintaining order.
 *
 * Return a pointer to a list containing both sets of arguments.
 * Whether to add the arguments to one of the lists or two make a third
 * list and add all arguments is up to implementation.
 */
struct ElementArray *concatArgLists(
    struct ElementArray *arr1, struct ElementArray *arr2);

#endif
