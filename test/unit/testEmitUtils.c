/*
 * Unit tests for the Utils module.
 */

#include <stdio.h>
#include <stdlib.h>

#include "testEmitUtils.h"
#include "EmitUtils.h"

char *test_growLabelStack() {
	struct labelStack *stack = newLabelStack();

	/* manually set the values */
	for (int i = 0; i < DEFAULT_LABEL_STACK_SIZE; i++) {
		stack->stack[i] = i;
	}

	/* grow the stack */
	growLabelStack(stack);

	/* make sure values are still good */
	for (int i = 0; i < DEFAULT_LABEL_STACK_SIZE; i++) {
		mu_assert("growLabelStack stomped some values :(",
		    stack->stack[i] == i);
	}
	for (int i = DEFAULT_LABEL_STACK_SIZE;
	    i < (DEFAULT_LABEL_STACK_SIZE*2); i++) {
		mu_assert("growLabelStack stomped some values :(",
		    stack->stack[i] == 0);
	}
	return NULL;
}


char *test_all_EmitUtils()
{
	mu_run_test(test_growLabelStack);
	return NULL;
}


