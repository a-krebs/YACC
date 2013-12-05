/*
 * Cmput 415 - Team YACC
 * Unit tests for the Hash module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>

#include "testTree.h"
#include "Tree.h"
#include "Definitions.h"


// mu_assert("",
// 		symbol == NULL);




char *test_tree() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol *symbol1 = createConstSymbol("test1");
	Symbol *symbol2 = createConstSymbol("test2");
	Symbol *symbol3 = createConstSymbol("test3");
	Symbol *symbol4 = createConstSymbol("test1");
	Symbol *symbol5 = createConstSymbol("test2");
	Symbol *symbol6 = createConstSymbol("test3");

	struct treeNode *left = createLeafNode(symbol2);	
	struct treeNode *right = createLeafNode(symbol3);

	struct treeNode *node = createTreeNode(symbol1, 6, left, right);

	struct treeNode *right2 = createLeafNode(symbol3);
	struct treeNode *node2 = createTreeNode(symbol1, 6, node, right2);

	mu_assert("Could not create tree node",
		node != NULL);

	mu_assert("Could not create tree node",
		node2 != NULL);

	mu_assert("Could not create tree node",
		node->left == left);	

	mu_assert("Could not create tree node",
		node->right == right);	

	mu_assert("Could not create tree node",
		right->parent == node && left->parent == node);	

	mu_assert("Could not create tree node",
		node2->left->left == left );	

	mu_assert("Could not create tree node",
		node2->left->right == right );	

	mu_assert("Could not create tree node",
		node2->right == right2 );	

	mu_assert("Could not create tree node",
		node2->right->right == NULL );	

	struct treeNode *right3 = createLeafNode(symbol4);
	struct treeNode *node3 = createTreeNode(symbol1, 88, node2, right3);

	mu_assert("Could not create tree node",
		node3->left == node2 );	

	mu_assert("Could not create tree node",
		node3->right == right3 );

	mu_assert("Could not create tree node",
		node3->left->left == node );		
		
	mu_assert("Could not create tree node",
		node3->left->left->left == left );					

	destroyHash(&table);
 	return NULL;
}



char *test_createTreeNode() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol *symbol1 = createConstSymbol("test1");
	Symbol *symbol2 = createConstSymbol("test2");
	Symbol *symbol3 = createConstSymbol("test3");

	struct treeNode *left = createLeafNode(symbol2);	
	struct treeNode *right = createLeafNode(symbol3);

	struct treeNode *node = createTreeNode(symbol1, 6, left, right);

	mu_assert("Could not create tree node",
		node != NULL);

	mu_assert("Unexpected value for opToken",
		node->opToken == 6);	

	mu_assert("Unexpected value for left",
		node->left != NULL);

	mu_assert("Unexpected value for right",
		node->right != NULL);

	mu_assert("Unexpected value for parent",
		node->parent == NULL);	

	mu_assert("Unexpected value for node's symbol name",
		strcmp(node->symbol->name, "test1") == 0);							

	mu_assert("Unexpected value for left after assingment",
		node->left == left);

	mu_assert("Unexpected value for right after assingment",
		node->right == right);	

	mu_assert("Unexpected value for parent from left",
		left->parent == node);			

	mu_assert("Unexpected value for paranet from right",
		right->parent == node);	

	mu_assert("Unexpected value for node's symbol name",
		strcmp(node->left->symbol->name, "test2") == 0);		

	destroyHash(&table);
        return NULL;
}


char *test_createLeafNode() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol *symbol = createConstSymbol("test");

	struct treeNode *node = createLeafNode(symbol);

	mu_assert("Could not create leaf tree node",
		node != NULL);

	mu_assert("Unexpected value for opToken",
		node->opToken == 0);	

	mu_assert("Unexpected value for left",
		node->left == NULL);

	mu_assert("Unexpected value for right",
		node->right == NULL);

	mu_assert("Unexpected value for parent",
		node->parent == NULL);	

	mu_assert("Unexpected value for node's symbol name",
		strcmp(node->symbol->name, "test") == 0);							

	destroyHash(&table);
        return NULL;
}

char *test_createNodeCommon() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol *symbol = createConstSymbol("test");
	struct treeNode *left = NULL;	
	struct treeNode *right = NULL;

	struct treeNode *node = createNodeCommon(symbol, 5, left, right);

	mu_assert("Could not create common tree node",
		node != NULL);

	mu_assert("Unexpected value for opToken",
		node->opToken == 5);	

	mu_assert("Unexpected value for left",
		node->left == NULL);

	mu_assert("Unexpected value for right",
		node->right == NULL);

	mu_assert("Unexpected value for parent",
		node->parent == NULL);						

	destroyHash(&table);
        return NULL;
}


char *test_allocateTreeNode() {
	struct treeNode *node = allocateTreeNode();

	mu_assert("Could not allocate tree node",
		node != NULL);

        return NULL;
}


char * test_all_Tree() {
	mu_run_test(test_allocateTreeNode);
	mu_run_test(test_createNodeCommon);
	mu_run_test(test_createLeafNode);
	mu_run_test(test_createTreeNode);
	mu_run_test(test_tree);
	
	return NULL;
}
