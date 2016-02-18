#include "arithmetic_integer_operations.h"

int main(int argc, char *argv[]) {
	int size = 4;
	unsigned * a = malloc(sizeof(unsigned) * 32);
	unsigned * b = malloc(sizeof(unsigned) * 32);
	int i;
	for (i = 0; i < 32; i++) {
		a[i] = 2;
		b[i] = 4;
	}

	unsigned * encode_a, * encode_b, * decode_a, * decode_b, * a_mul_b_encoded, *a_mul_b_decoded; 
	encode_a = calloc(size, sizeof(unsigned));
	encode_b = calloc(size, sizeof(unsigned));
	decode_a = calloc(size, sizeof(unsigned));	
	decode_b = calloc(size, sizeof(unsigned));
	a_mul_b_encoded = calloc(size, sizeof(unsigned));			
	a_mul_b_decoded = calloc(32, sizeof(unsigned));		

	encode_bitslice(a, encode_a, size);
	encode_bitslice(b, encode_b, size);	

	int carry = 0;
	multiply(encode_a, encode_b, size, a_mul_b_encoded);
	print_binary_array(a_mul_b_encoded, size);
	printf("%d\n", carry);

	decode_bitslice(a_mul_b_encoded, a_mul_b_decoded, size);
	print_binary_array(a_mul_b_decoded, size);

	// encode_bitslice(a, encode_a, size);
	// encode_bitslice(b, encode_b, size);
	// print_binary_array(encode_a, size);
	// print_binary_array(encode_b, size);

	// decode_bitslice(encode_a, decode_a, size);
	// decode_bitslice(encode_b, decode_b, size);
	// print_binary_array(decode_a, size);
	// print_binary_array(decode_b, size);
	return 0;
}