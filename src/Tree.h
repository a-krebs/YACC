#ifndef TREE_H
#define TREE_H

#define NO_OPT -1
#define ARRAY_INDEX -2
#define RECORD_ACCESS -3


struct treeNode {
	struct Symbol *symbol;
	int opToken;
	struct treeNode *parent;
	struct treeNode *left;
	struct treeNode *right;
};


Symbol *postOrderWalk(struct treeNode *node);

struct treeNode *allocateTreeNode();

struct treeNode *createNodeCommon(Symbol *symbol, int opToken, 
	struct treeNode *left, struct treeNode *right );

struct treeNode *createTreeNode(Symbol *symbol, int opToken,
	struct treeNode *left, struct treeNode *right);

struct treeNode *createLeafNode(Symbol *symbol);

struct treeNode *createRecordNode(Symbol *symbol, struct treeNode *child);
#endif
