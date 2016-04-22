#ifndef ARITHMETIC_INTEGER_OPERATIONS_H
#define	ARITHMETIC_INTEGER_OPERATIONS_H

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_helper.h"
#include "circuits.h"

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

char * output_add(
	char * first,
	char * second,
	char * carry,
	int size,
	char * result); 

void multiply(
	unsigned * first,
	unsigned * second,
	int size_first,
	int size_second,
	unsigned * result);

char * output_multiply_algorithm(
	char * first,
	char * second,
	int size_first,
	int size_second,
	char * result);

void mapAnd(
	unsigned * array,
	unsigned * result,
	unsigned operand,
	int size);

char * output_map_and(
	char * array,
	char * result,
	char * operand,
	int size);

void encode_bitslice(
	unsigned * input,
	unsigned * output,
	int size);

void decode_bitslice(
	unsigned * input,
	unsigned * output,
	int size);

void print_binary_array(unsigned * array, int size);

#endif