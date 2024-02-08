#ifndef __ICE_ARRAY__
#define __ICE_ARRAY__

#include <stdlib.h>
#include <string.h>

#include "ice_allocator.h"

//
// Constants
//

/**
 * The default capacity of an array
*/
#define ARRAY_DEFAULT_CAPACITY 16

//
// Macros
//

/**
 * Get the header of an array
 * @param array The array
 * @return The header of the array
 * @note This is a macro
*/
#define get_ice_array_header(array) \
	( \
		(ice_array_header*)(array) - 1 \
	)

/**
 * Get the length of an array
 * @param array The array
 * @return The length of the array
 * @note This is a macro
*/
#define ice_array_len(array) \
	( \
		get_ice_array_header(array)->len \
	)

/**
 * Get the capacity of an array
 * @param array The array
 * @return The capacity of the array
 * @note This is a macro
*/
#define ice_array_capacity(array) \
	( \
		get_ice_array_header(array)->capacity \
	)

/**
 * Create a new array
 * @param T The type of the array
 * @param allocator The allocator to use
 * @return A pointer to the new array
 * @note This is a macro
*/
#define ice_array(T, allocator) \
	(T*)ice_array_init(sizeof(T), ARRAY_DEFAULT_CAPACITY, allocator)

/**
 * Append an item to an array
 * @param array The array
 * @param value The value to append
 * @return A pointer the the appended value
 * @note This is a macro
*/
#define ice_array_append(array, value) \
	( \
		(array) = ice_array_ensure_capacity(array, 1, sizeof(value)), \
		(array)[get_ice_array_header(array)->len] = (value), \
		&(array)[get_ice_array_header(array)->len++] \
	)

/**
 * Remove an item from an array
 * @param array The array
 * @param index The index of the item to remove
 * @return A pointer the the array
 * @note This is a macro
*/
#define ice_array_remove(array, index) \
	do { \
		ice_array_header* header = get_ice_array_header(array); \
		if (index == header->len - 1) { \
			header->len -= 1; \
		} else if (header->len > 1) { \
			void* ptr = &array[index]; \
			void* last = &array[header->len - 1]; \
			header->len -= 1; \
			memcpy(ptr, last, sizeof(*array)); \
		} \
	} while (0);

/**
 * Pop an item from the back of an array
 * @param array The array
 * @return A pointer the the array
 * @note This is a macro
*/
#define ice_array_pop_back(array) \
	( \
		get_ice_array_header(array)->len -= 1 \
	)

//
// Struct Definitions
//

/**
 * The header of an array
*/
typedef struct ice_array_header ice_array_header;

struct ice_array_header {
	/**
	 * The capacity of the array
	*/
	size_t capacity;
	/**
	 * The length of the array
	*/
	size_t len;
	/**
	 * The allocator to use
	*/
	ice_allocator* allocator;
};

//
// Function Prototypes
//

/**
 * Ensure the capacity of an array
 * @param array The array
 * @param item_count The number of items to add
 * @param item_size The size of each item
 * @return A pointer to the array
 * @note This is a private function
*/
void* ice_array_ensure_capacity(void* array, size_t item_count, size_t item_size);

/**
 * Initialize a new array
 * @param item_size The size of each item
 * @param capacity The capacity of the array
 * @param allocator The allocator to use
 * @return A pointer to the new array
 * @deprecated Use the ice_array macro instead
*/
void* ice_array_init(size_t item_size, size_t capacity, ice_allocator* allocator);

/**
 * Push an item to the back of an array
 * @param array The array
 * @param item The item to push
 * @deprecated Use the ice_array_append macro instead
*/
void ice_array_push(void* array, void* item);

//
// Function Definitions
//

void* ice_array_ensure_capacity(void* array, size_t item_count, size_t item_size) {
    ice_array_header* header = get_ice_array_header(array);
    size_t desired_capacity = header->len + item_count;

    if(header->capacity < desired_capacity) {
        size_t new_capacity = header->capacity * 2;
        while(new_capacity < desired_capacity) {
            new_capacity *= 2;
        }

        size_t new_size = sizeof(ice_array_header) + new_capacity * item_size;
        ice_array_header* new_header = header->allocator->alloc(new_size, header->allocator->context);

        if(new_header) {
            size_t old_size = sizeof(*header) + header->len * item_size;
            memcpy(new_header, header, old_size);

			if(header->allocator->free) {
            	header->allocator->free(old_size, header, header->allocator->context);
			}

            new_header->capacity = new_capacity;
            header = new_header + 1;
        } else {
            header = 0;
        }
    } else { header += 1; }

    return header;
}

void* ice_array_init(size_t item_size, size_t capacity, ice_allocator* allocator) {
	void* ptr = 0;
	size_t size = sizeof(ice_array_header) + (item_size * capacity);
	ice_array_header* header = allocator->alloc(size, allocator->context);

	if(header) {
		header->capacity = capacity;
		header->len = 0;
		header->allocator = allocator;
		ptr = header + 1;
	}

	return ptr;
}

void ice_array_push(void* array, void* item) {
	ice_array_header* header = (ice_array_header*)array - 1;
	if(header->len == header->capacity) {
		size_t new_capacity = header->capacity * 2;
		size_t new_size = sizeof(ice_array_header) + (header->capacity * new_capacity);
		header = (ice_array_header*)realloc(header, new_size);
		header->capacity = new_capacity;
		array = header + 1;
	}
	memcpy((char*)array + (header->len * header->capacity), item, header->capacity);
	header->len++;
}

#endif // __ICE_ARRAY__