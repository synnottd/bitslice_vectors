##include "arithmetic_integer_operations.h"

void add(
	unsigned * first,
	unsigned * second,
	int * carry,
	int size,
	unsigned * result) 
{
	unsigned first_xor_second;
	int i;
	for (i = 0; i < size; i++) {
		first_xor_second = first[i] ^ second[i];
		result[i] = first_xor_second ^ carry;
		carry = (carry & first_xor_second) | (first & second);
	}
}


//http://www.csie.nuk.edu.tw/~wuch/course/eea051/eea051-04.pdf
void multiply(
	unsigned * first,
	unsigned * second,
	int size,
	unsigned * result) 
{	
	unsigned * temp = alloc(sizeof(unsigned) * (size));
	result = calloc(sizeof(unsigned) * 2 * size );
	result[size] = 0;
	int i, carry;

	mapAnd(second, , first[0], size);
	for(i = 1; i < size; i++) {
		mapAnd(second, carry, first[i], size);
		add(result[i], temp, &carry, size, result[i]);
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

