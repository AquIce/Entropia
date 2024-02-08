#ifndef __ENT_FRONT_LEX__
#define __ENT_FRONT_LEX__

#include <stdbool.h>
#include <ctype.h>

#include "lib/ice_str.h"
#include "lib/ice_array.h"
#include "lib/ice_allocator.h"

#include "ent_types_token.h"

/**
 * ent_front_lex
 * 
 * @param src: the source string to lex
 * @param tokens: the tokens to fill
 * 
 * @return 0 if successful, 1 if not
*/
int ent_front_lex(ice_str* src, ent_type_token** tokens, ice_allocator* alloc) {
	// Create an empty token
	ent_type_token* tk = ent_type_token_new_empty(alloc);
	// Iterate through the source string
	while(ice_str_len(src) > 0) {
		// Print the source string
		printf("\"%s\"\n", src->data);
		// Print the current character
		printf("'%c'\n", ice_str_lookup(src));
		// Set the value of the token to an empty string
		tk->value = ice_str_new_empty(alloc);
		// If the current character is a space, skip it
		if(ice_str_lookup(src) == ' ') {
			ice_str_shift(src);
			continue;
		} else if(ice_str_lookup(src) == '(') { // If the current character is a left parenthesis
			ST_TOKEN(
				OPEN_PAREN,
				ice_str_shift(src),
				alloc
			);
		} else if(ice_str_lookup(src) == ')') { // If the current character is a right parenthesis
			ST_TOKEN(
				CLOSE_PAREN,
				ice_str_shift(src),
				alloc
			);
		} else if(isdigit(ice_str_lookup(src))) { // If the current character is a digit
			ice_str* value = ice_str_new_empty(alloc);
			while(isdigit(ice_str_lookup(src))) {
				ice_str_append_char(value, ice_str_shift(src), alloc);
			}
			ST_MTOKEN(
				NUMBER,
				value->data,
				alloc
			);
		} else if(ice_str_lookup(src) == '+' || ice_str_lookup(src) == '-' || ice_str_lookup(src) == '*' || ice_str_lookup(src) == '/') { // If the current character is an operator
			ST_TOKEN(
				OPERATOR,
				ice_str_shift(src),
				alloc
			);
		} else {
			printf("Unknown character: '%c'\n", ice_str_lookup(src));
			return 1;
		}
		printf("TOKEN\n%s\n", pretty_print_token(tk, alloc));
		ice_array_append(tokens, tk);
	}
	return 0;
}

#endif // __ENT_FRONT_LEX__