#ifndef TREE_H
#define TREE_H

#define NO_OPT -1

struct treeNode {
	struct Symbol *symbol;
	int opToken;
	struct treeNode *parent;
	struct treeNode *left;
	struct treeNode *right;
};


struct treeNode *allocateTreeNode();

struct treeNode *createNodeCommon(Symbol *symbol, int opToken, 
	struct treeNode *left, struct treeNode *right );

struct treeNode *createTreeNode(Symbol *symbol, int opToken,
	struct treeNode *left, struct treeNode *right);

struct treeNode *createLeafNode(Symbol *symbol);

#endif