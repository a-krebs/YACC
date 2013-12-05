#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Definitions.h"
#include "Tree.h"
#include "Emit.h"



#ifndef TESTBUILD
#include "parser.tab.h"	/* token definitions used in operator compat checks */
#endif
#ifdef TESTBUILD
#include "tokens.h"
#endif


/*
	questions:
		- should no op be 0?


*/


void emitBabyTree(Symbol *x, int opToken, Symbol *y) {

	switch (opToken) {
		case PLUS:
			emitAddition( (Symbol *) x, (Symbol *) y);
			break;
		default:
			printf("FUCK MY LIFE\n");
	}
}


Symbol *postOrderWalk(struct treeNode *node) {
	Symbol *x = NULL;
	Symbol *y = NULL;

	if (node->left == NULL) {
		return node->symbol;
	}
	else {
		x = postOrderWalk(node->left);
		y = postOrderWalk(node->right);
		emitBabyTree(x, node->opToken, y);
		return node->symbol;
	}
}		


struct treeNode *allocateTreeNode() {
	struct treeNode *node = calloc(1, sizeof(struct treeNode));

	if ( node == NULL ) {
		err(1, "Could not alloc memory for tree node.");
		exit(EXIT_FAILURE);		
	}

	return node;
}


struct treeNode *createNodeCommon(Symbol *symbol, int opToken, 
	struct treeNode *left, struct treeNode *right ) 
{
	struct treeNode *node = allocateTreeNode();
	
	node->symbol = symbol;
	node->opToken = opToken;
	node->parent = NULL;
	node->left = left;
	node->right = right;

	return node;
}


struct treeNode *createTreeNode(Symbol *symbol, int opToken,
	struct treeNode *left, struct treeNode *right) 
{
	struct treeNode *node = NULL;

	node = createNodeCommon(symbol, opToken, left, right);	
	node->left->parent = node;
	node->right->parent = node;

	return node;
}


struct treeNode *createLeafNode(Symbol *symbol) 
{
	struct treeNode *node = NULL;

	node = createNodeCommon(symbol, NO_OPT, NULL, NULL);

	return node;
}