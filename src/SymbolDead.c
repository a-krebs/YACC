/* Checks each memeber of the passed ElementArray to see if each
 * memeber is of simple type.
 *
 * Parameters:
 *              elementArray: elementArray passed
 *
 * Return: Boolean: 1 if elemetn array is simple
 *		    0 if not
 */
int isElementArraySimple(struct ElementArray *elementArray) {
	struct Symbol *symbol;
	type_t symbolsType;

	for (int i = 0; i < elementArray->nElements; ++i) {
		symbol = (struct Symbol *) getElementAt(elementArray, i);

		if ( symbol->kind != TYPE_KIND ) {
			return 0;
		}

		symbolsType = getType(symbol);

		if ( symbolsType != BOOLEAN_T
			&& symbolsType != CHAR_T
			&& symbolsType != INTEGER_T
			&& symbolsType != REAL_T
			&& symbolsType != STRING_T ) {
			return 0;
		}
	}

	return 1;
}


/*
 * Follows the chains of next pointer to get the size of the Symbol linked
 * list.
 */
// int
// getSymbolListLength(Symbol *s)
// {	
// 	int len = 0;
// 	while (s) {
// 		len++;
// 		s = s->next;
// 	}
// 	return len;
// }