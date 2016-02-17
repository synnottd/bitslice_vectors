##include "arithmetic_integer_operations.h"

void add(
	unsigned * first,
	unsigned * second,
	int size,
	unsigned * result) 
{
	unsigned first_xor_second, carry = 0;
	int i;
	for (i = 0; i < size; i++) {
		first_xor_second = first[i] ^ second[i];
		result[i] = first_xor_second ^ carry;
		carry = (carry & first_xor_second) | (first & second);
	}
}

