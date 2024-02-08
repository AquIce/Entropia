#include <stdio.h>

#include "lib/ice_str.h"
#include "lib/ice_allocator.h"
#include "lib/ice_array.h"

#include "ent_front_lex.h"
#include "ent_types_token.h"

ice_allocator alloc = {
	ice_alloc,
	ice_realloc,
	ice_free,
	0
};

int main() {
	ice_str* src = ice_str_new("1 + 2 * 3", &alloc);
	ent_type_token** tokens = ice_array(ent_type_token*, &alloc);
	int status = ent_front_lex(src, tokens, &alloc);
	printf("Status: %d\n", status);
	if(status) {
		printf("Failed to lex\n");
		return 1;
	}
	printf("Tokens:\n");
	for(int i = 0; i < ice_array_len(tokens); i++) {
		printf("%s\n", pretty_print_token(*tokens + i, &alloc));
		alloc.free(sizeof tokens[i], tokens[i], alloc.context);
	}
	alloc.free(sizeof tokens, tokens, alloc.context);
	return 0;
}