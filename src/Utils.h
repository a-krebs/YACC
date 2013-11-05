#ifndef UTILS_H
#define UTILS_H

#include "Definitions.h"

int isLogicalOperator(int);
int isRelationalOperator(int);
int isUnaryOperator(int);
Symbol * numOpResult(Symbol *, Symbol *, int);
type_t numOpIntLHS(int);
type_t numOpRealLHS(int);

#endif
