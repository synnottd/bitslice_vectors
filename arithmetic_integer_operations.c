#include "arithmetic_integer_operations.h"


void add(
	unsigned * first,
	unsigned * second,
	int * carry,
	int size,
	unsigned * result) 
{
	unsigned first_xor_second, temp_result;
	int i;
	for (i = 0; i < size; i++) {
		first_xor_second = first[i] ^ second[i];
		temp_result = first_xor_second ^ *carry;
		*carry = (*carry & first_xor_second) | (first[i] & second[i]);
		result[i] = temp_result;
	}
}


//http://www.csie.nuk.edu.tw/~wuch/course/eea051/eea051-04.pdf
void multiply(
	unsigned * first,
	unsigned * second,
	int size,
	unsigned * result) 
{	
	unsigned * temp = malloc(sizeof(unsigned) * (size));
	result[size] = 0;
	int i, carry;
	carry = 0;
	mapAnd(second, result, first[0], size);
	for(i = 1; i < size / 2 ; i++) {
		mapAnd(second, temp, first[i], size);
		add(&result[i], temp, &carry, size - i, &result[i]);
		result[i + size] = carry;
	}
}

void mapAnd(
	unsigned * array,
	unsigned * result,
	unsigned operand,
	int size)
{
	int i;
	for (i = 0; i < size; i++) {
		result[i] = array[i] & operand;
	}
}

void encode_bitslice(
	unsigned * input,
	unsigned * output,
	int size)
{

	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < sizeof(unsigned) * CHAR_BIT; j++) {
			output[i] |= ((input[j] & (1 << i)) && 1) << j;
		}
	}
}

void decode_bitslice(
	unsigned * input,
	unsigned * output,
	int size)
{
	int i, j;

	for (i = 0; i < (sizeof(unsigned) * CHAR_BIT); i++) {
		for (j = 0; j < size; j++) {
			output[i] |= ((input[j] & (1 << i)) && 1) << j;
		}
	}
}

void print_binary_array(unsigned * array, int size) 
{
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = (sizeof(unsigned) * CHAR_BIT) - 1; j >= 0; j--) {
			printf("%d",  (array[i] & (1 << j)) ? 1 : 0) ;
		}
		printf("\n");
	}
}

// void 2x2_multipler(
// 	unsigned * first,
// 	unsigned * second,
// 	unsigned * result
// 	)
// {
// 	int temp, temp2;
// 	result[0] = first[0] & second[0];
// 	temp = first[1] & second[0];
// 	temp2 = first[0] & second[1];
// 	result[1] = temp ^ temp2;
// 	temp = temp & temp2;
// 	temp2 = first[1] & second[1];
// 	result[2] = temp ^ temp2;
// 	result[3] = temp & temp2;
// }

// void 4x4_multiplier(
// 	unsigned * first,
// 	unsigned * second,
// 	unsigned * result
// 	)
// {

// }

