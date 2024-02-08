#ifndef __ICE_STR__
#define __ICE_STR__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ice_allocator.h"

/**
 * ice_str
*/
typedef struct ice_str ice_str;

struct ice_str {
	/**
	 * The allocated size of the string
	*/
	size_t alloc;
	/**
	 * The length of the string
	*/
	size_t len;
	/**
	 * The address of the string
	*/
	char* data;
};

//
// Private function prototypes
//

/**
 * Ensure that an ice_str object has enough capacity
 * @param str The ice_str object
 * @param new_size The new size to ensure
 * @return Whether the string has enough capacity
 * @note This is a private function
*/
bool ice_str_ensure_capacity(ice_str* str, size_t new_size);

/**
 * Reallocate an ice_str object
 * @param str The ice_str object
 * @param new_size The new size to reallocate
 * @return A pointer to the new string
 * @note This is a private function
*/
char* ice_str_reallocate(ice_str* str, size_t new_size, ice_allocator* alloc);

//
// Public function prototypes
//

/**
 * Create a new ice_str object
 * @return A pointer to the new ice_str object
*/
ice_str* ice_str_new_empty(ice_allocator* alloc);

/**
 * Create a new ice_str object
 * @param data The initial data to store in the string
 * @return A pointer to the new ice_str object
*/
ice_str* ice_str_new_char(char data, ice_allocator* alloc);

/**
 * Create a new ice_str object
 * @param data The initial data to store in the string
 * @return A pointer to the new ice_str object
*/
ice_str* ice_str_new(const char *data, ice_allocator* alloc);

/**
 * Get the C string from an ice_str object
 * @param str The ice_str object
 * @return A pointer to the C string
*/
char* ice_str_cstr(ice_str* str);

/**
 * Append a char to an ice_str object
 * @param str The ice_str object
 * @param data The char to append
 * @return A pointer to the C string
*/
char* ice_str_append_char(ice_str* str, char data, ice_allocator* alloc);

/**
 * Append a C string to an ice_str object
 * @param str The ice_str object
 * @param data The C string to append
 * @return A pointer to the C string
*/
char* ice_str_append_cstr(ice_str* str, const char* data, ice_allocator* alloc);

/**
 * Append an ice_str object to another ice_str object
 * @param str The ice_str object
 * @param data The ice_str object to append
 * @return A pointer to the C string
*/
char* ice_str_append_str(ice_str* str, ice_str* data, ice_allocator* alloc);

/**
 * Free an ice_str object
 * @param str The ice_str object
 * @return void
*/
void ice_str_free(ice_str* str, ice_allocator* alloc);

/**
 * Look up the first character in an ice_str object
 * @param str The ice_str object
 * @return The character at the beginning of the string
*/
char ice_str_lookup(ice_str* str);

/**
 * Shift the first character of an ice_str object
 * @param str The ice_str object
 * @return The first character of the string
*/
char ice_str_shift(ice_str* str);

/**
 * Get the length of an ice_str object
 * @param str The ice_str object
 * @return The length of the string
*/
size_t ice_str_len(ice_str* str);

//
// Private function implementations
//

bool ice_str_ensure_capacity(ice_str* str, size_t new_size) {
	return new_size <= str->alloc;
}

char* ice_str_reallocate(ice_str* str, size_t new_size, ice_allocator* alloc) {
	str->alloc = new_size;
	str->data = alloc->realloc(sizeof str->data, str->data, alloc->context);
	return str->data;
}

// 
// Public function implementations
//

ice_str* ice_str_new_empty(ice_allocator* alloc) {
	ice_str* str = alloc->alloc(sizeof(ice_str), alloc->context);
	str->alloc = 1;
	str->data = alloc->alloc(str->alloc, alloc->context);
	str->data[0] = '\0';
	str->len = 0;
	return str;
}

ice_str* ice_str_new_char(char data, ice_allocator* alloc) {
	ice_str* str = ice_str_new_empty(alloc);
	ice_str_append_char(str, data, alloc);
	return str;
}

ice_str* ice_str_new(const char *data, ice_allocator* alloc) {
	ice_str* str = ice_str_new_empty(alloc);
	ice_str_append_cstr(str, data, alloc);
	return str;
}

char* ice_str_cstr(ice_str* str) {
	return str->data;
}

char* ice_str_append_char(ice_str* str, char data, ice_allocator* alloc) {
	if(!ice_str_ensure_capacity(str, str->len + 1)) {
		ice_str_reallocate(str, str->alloc + 1, alloc);
	}
	str->data[str->len] = data;
	str->len++;
	str->data[str->len] = '\0';
	return str->data;
}

char* ice_str_append_cstr(ice_str* str, const char* data, ice_allocator* alloc) {
	for(size_t i = 0; data[i] != '\0'; i++) {
		ice_str_append_char(str, data[i], alloc);
	}
	return str->data;
}

char* ice_str_append_str(ice_str* str, ice_str* data, ice_allocator* alloc) {
	ice_str_append_cstr(str, data->data, alloc);
	return str->data;
}

void ice_str_free(ice_str* str, ice_allocator* alloc) {
	alloc->free(sizeof str->data, str->data, alloc->context);
	alloc->free(sizeof str, str, alloc->context);
}

char ice_str_lookup(ice_str* str) {
	return str->data[0];
}

char ice_str_shift(ice_str* str) {
	char c = ice_str_lookup(str);
	for(size_t i = 0; i < str->len; i++) {
		str->data[i] = str->data[i + 1];
	}
	str->len--;
	return c;
}

size_t ice_str_len(ice_str* str) {
	return str->len;
}

#endif // __ICE_STR__