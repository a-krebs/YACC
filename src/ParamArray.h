/*
 * Module implementing a simple list type structure for function/procedure
 * parameters.
 */

#ifndef PARAMARRAY_H
#define PARAMARRAY_H

#include "Type.h"

#define PA_DEFAULT_SZ 24	/* default initial size of param array */

struct ParamArray *newParamArray();
void appendParam(struct ParamArray *, struct Param *);
struct Param *getParam(struct ParamArray *, unsigned int);
void freeParamArray(struct ParamArray *); 
void growParamArray(struct ParamArray *); 

#endif
