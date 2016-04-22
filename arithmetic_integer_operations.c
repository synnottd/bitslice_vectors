#include "arithmetic_integer_operations.h"


void add(
	unsigned * first,
	unsigned * second,
	unsigned * carry,
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

char * output_add(
	char * first,
	char * second,
	char * carry,
	int size,
	char * result) 
{ // assumes unsigned first_xor_second, temp_result;
	char * output = malloc(sizeof(char) * 10000);
	char * first_ = malloc(sizeof(char) * 100);
	char * second_ = malloc(sizeof(char) * 100);
	char * result_ = malloc(sizeof(char) * 100);
	char * temp;
	sprintf(output, "unsigned a_xor_b, a_xor_b_and_c, a_and_b;\n");
	for (int i = 0; i < size; i++) {
		sprintf(first_, "%s[%d]", first, i);
		sprintf(second_, "%s[%d]", second, i);
		sprintf(result_, "%s[%d]", result, i);
		temp = full_adder_output(first_, second_, carry, result_, carry);
		sprintf(output + strlen(output), "%s", temp);
		free(temp);
	}
	//trim removes trailing whitespace
	return trim(output);
}

void signed_add(
	int * first,
	int * second,
	int * carry,
	int * overflow,
	int size,
	int * result) 
{	
	*overflow = (first[size - 1] & first[size - 1] & ~result[size - 1]) | (~first[size - 1] & ~first[size - 1] & result[size - 1]);
	printf("%d\n", *overflow);
	add(
		(unsigned *) first,
		(unsigned *) second,
		(unsigned *) carry,
		(int) size,
		(unsigned *) result);
}


//http://www.csie.nuk.edu.tw/~wuch/course/eea051/eea051-04.pdf
void multiply(
	unsigned * first,
	unsigned * second,
	int size_first,
	int size_second,
	unsigned * result) 
{	
	unsigned * temp = malloc(sizeof(unsigned) * size_second);
	temp[size_first - 1] = 0;
	int i;
	unsigned carry = 0;
	mapAnd(second, result, first[0], size_second);
	for(i = 1; i < size_first ; i++) {
		mapAnd(second, temp, first[i], size_second);
		add(&result[i], temp, &carry, size_second, &result[i]);
		result[i + size_first] = carry;
	}
}

char * output_multiply_algorithm(
	char * first,
	char * second,
	int size_first,
	int size_second,
	char * result)
{
	char * output = malloc(sizeof(char) * 100000);
	sprintf(output + strlen(output), "unsigned * temp = malloc(sizeof(unsigned) * (%d));\n", size_second);
	sprintf(output + strlen(output), "temp[%d] = 0;\n", size_first - 1);
	sprintf(output + strlen(output), "unsigned carry, first_xor_second, temp_result;\n");
	char * temp = malloc(sizeof(char) * 1000);
	sprintf(temp, "%s[0]", first);
	sprintf(output + strlen(output), "%s", output_map_and(second, result, temp, size_second));
	int i;
	for(i = 1; i < size_first ; i++) {
		sprintf(temp, "%s[%d]", first, i);
		sprintf(output + strlen(output), "%s", output_map_and(second, "temp", temp, size_second));
		sprintf(temp, "%s + %d", result, i);
		sprintf(output + strlen(output), "%s", output_add(result, "temp", "carry", size_second, result));
		sprintf(output + strlen(output), "%s[%d] = carry;\n", result, i + size_first);
	}
	return trim(output);
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

char * output_map_and(
	char * array,
	char * result,
	char * operand,
	int size)
{	
	char * output = malloc(sizeof(char) * 100000);
	int i;
	for (i = 0; i < size; i++) {
		sprintf(output + strlen(output), "%s[%d] = %s[%d] & %s;\n", result, i, array, i, operand);
	}
	return trim(output);
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

	for (i = 0; i < sizeof(unsigned) * CHAR_BIT; i++) {
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

