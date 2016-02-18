#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

void add(
	unsigned * first,
	unsigned * second,
	unsigned * carry,
	int size,
	unsigned * result);

void signed_add(
	int * first,
	int * second,
	int * carry,
	int * overflow,
	int size,
	int * result);

void multiply(
	unsigned * first,
	unsigned * second,
	int size,
	unsigned * result);

void mapAnd(
	unsigned * array,
	unsigned * result,
	unsigned operand,
	int size);

void encode_bitslice(
	unsigned * input,
	unsigned * output,
	int size);

void decode_bitslice(
	unsigned * input,
	unsigned * output,
	int size);

void print_binary_array(unsigned * array, int size) ;