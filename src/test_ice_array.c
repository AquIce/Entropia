#include <stdio.h>
#include <assert.h>

#include "lib/ice_allocator.h"
#include "lib/ice_array.h"

//
// Test suite for the ice_array library
//

int testNb = 1;

void test_ice_array_init(ice_allocator* allocator) {
	testNb = 1;
	int* array = ice_array(int, allocator);
	assert(ice_array_len(array) == 0);
	printf("\t-> %d: Array length 0 after initialization [OK]\n", testNb++);
	assert(ice_array_capacity(array) == ARRAY_DEFAULT_CAPACITY);
	printf("\t-> %d: Array capacity %d after initialization [OK]\n", testNb++, ARRAY_DEFAULT_CAPACITY);
}

void test_ice_array_append(ice_allocator* allocator) {
	testNb = 1;
	int* array = ice_array(int, allocator);
	ice_array_append(array, 1);
	assert(ice_array_len(array) == 1);
	printf("\t-> %d: Array length 1 after appending [OK]\n", testNb++);
	assert(ice_array_capacity(array) == ARRAY_DEFAULT_CAPACITY);
	printf("\t-> %d: Array capacity %d after appending [OK]\n", testNb++, ARRAY_DEFAULT_CAPACITY);
	ice_array_append(array, 2);
	assert(ice_array_len(array) == 2);
	printf("\t-> %d: Array length 2 after appending [OK]\n", testNb++);
	assert(ice_array_capacity(array) == ARRAY_DEFAULT_CAPACITY);
	printf("\t-> %d: Array capacity %d after appending [OK]\n", testNb++, ARRAY_DEFAULT_CAPACITY);
	ice_array_append(array, 3);
	assert(ice_array_len(array) == 3);
	printf("\t-> %d: Array length 3 after appending [OK]\n", testNb++);
	assert(ice_array_capacity(array) == ARRAY_DEFAULT_CAPACITY);
	printf("\t-> %d: Array capacity %d after appending [OK]\n", testNb++, ARRAY_DEFAULT_CAPACITY);
}

void test_ice_array_remove(ice_allocator* allocator) {
	testNb = 1;
	int* array = ice_array(int, allocator);
	ice_array_append(array, 1);
	ice_array_append(array, 2);
	ice_array_append(array, 3);
	ice_array_remove(array, 1);
	assert(ice_array_len(array) == 2);
	printf("\t-> %d: Array length 2 after removing [OK]\n", testNb++);
	assert(ice_array_capacity(array) == ARRAY_DEFAULT_CAPACITY);
	printf("\t-> %d: Array capacity %d after removing [OK]\n", testNb++, ARRAY_DEFAULT_CAPACITY);
	assert(array[0] == 1);
	printf("\t-> %d: Array[0] == 1 after removing [OK]\n", testNb++);
	assert(array[1] == 3);
	printf("\t-> %d: Array[1] == 3 after removing [OK]\n", testNb++);
}

void test_ice_array_pop_back(ice_allocator* allocator) {
	testNb = 1;
	int* array = ice_array(int, allocator);
	ice_array_append(array, 1);
	ice_array_append(array, 2);
	ice_array_append(array, 3);
	ice_array_pop_back(array);
	assert(ice_array_len(array) == 2);
	printf("\t-> %d: Array length 2 after popping back [OK]\n", testNb++);
	assert(ice_array_capacity(array) == ARRAY_DEFAULT_CAPACITY);
	printf("\t-> %d: Array capacity %d after popping back [OK]\n", testNb++, ARRAY_DEFAULT_CAPACITY);
	assert(array[0] == 1);
	printf("\t-> %d: Array[0] == 1 after popping back [OK]\n", testNb++);
	assert(array[1] == 2);
	printf("\t-> %d: Array[1] == 2 after popping back [OK]\n", testNb++);
}

int main() {
	ice_allocator my_allocator = {ice_alloc, ice_free, 0};
	printf("Running tests...\n");
	printf("ice_array_init\n");
	test_ice_array_init(&my_allocator);
	printf("ice_array_append\n");
	test_ice_array_append(&my_allocator);
	printf("ice_array_append\n");
	test_ice_array_remove(&my_allocator);
	printf("ice_array_remove\n");
	test_ice_array_pop_back(&my_allocator);
	printf("ice_array_pop_back\n");
	assert(1 == 0);
	printf("All tests passed!\n");
	return 0;
}