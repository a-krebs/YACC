#ifndef TREE_H
#define TREE_H

struct treeNode {
	struct Symbol *symbol;
	int opToken;
	struct treeNode *parent;
	struct treeNode *left;
	struct treeNode *right;
};

#endif