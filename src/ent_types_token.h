#ifndef __ENT_TYPES_TOKEN__
#define __ENT_TYPES_TOKEN__

#include "lib/ice_str.h"
#include "lib/ice_allocator.h"

enum ent_type_token_type {
    OPERATOR,

    OPEN_PAREN,
    CLOSE_PAREN,

    NUMBER,
};

typedef struct ent_type_token ent_type_token;

struct ent_type_token {
    enum ent_type_token_type type;
	ice_str* value;
};

ent_type_token* ent_type_token_new(enum ent_type_token_type type, ice_str* value, ice_allocator* alloc) {
	ent_type_token* tk = alloc->alloc(sizeof(ent_type_token), alloc->context);
	tk->type = type;
	tk->value = value;
	return tk;
}

ent_type_token* ent_type_token_new_empty(ice_allocator* alloc) {
	return ent_type_token_new(0, ice_str_new_empty(alloc), alloc);
}

ent_type_token* ST_TOKEN(enum ent_type_token_type type, char value, ice_allocator* alloc) {
	return ent_type_token_new(type, ice_str_new_char(value, alloc), alloc);
}

ent_type_token ST_MTOKEN(enum ent_type_token_type type, const char* value, ice_allocator* alloc) {
	ent_type_token_new(type, ice_str_new(value, alloc), alloc);
}

char* pretty_print_token(ent_type_token* token, ice_allocator* alloc) {
	ice_str* type = ice_str_new("UNKNOWN", alloc);
	printf("Token type: %d\n", token->type);
	printf("Token value: %s\n", token->value->data);
	switch(token->type) {
		case OPERATOR:
			type = ice_str_new("OPERATOR", alloc);
			break;
		case OPEN_PAREN:
			type = ice_str_new("OPEN_PAREN", alloc);
			break;
		case CLOSE_PAREN:
			type = ice_str_new("CLOSE_PAREN", alloc);
			break;
		case NUMBER:
			type = ice_str_new("NUMBER", alloc);
			break;
	}
	ice_str_append_cstr(type, ": ", alloc);
	ice_str_append_str(type, token->value, alloc);
	return type->data;
}

#endif // __ENT_TYPES_TOKEN__