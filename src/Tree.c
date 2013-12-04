#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Definitions.h"
#include "Tree.h"



/*
	questions:
		- should no op be 0?


*/



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