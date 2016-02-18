#include "arithmetic_integer_operations.h"

int main(int argc, char *argv[]) {
	int size = 3;
	int * a = malloc(sizeof(int) * 32);
	int * b = malloc(sizeof(int) * 32);
	int i;
	for (i = 0; i < 32; i++) {
		a[i] = -1;
		b[i] = -4;
	}

	int * encode_a, * encode_b, * decode_a, * decode_b, * a_x_b_encoded, *a_x_b_decoded; 
	encode_a = calloc(size, sizeof(int));
	encode_b = calloc(size, sizeof(int));
	decode_a = calloc(size, sizeof(int));	
	decode_b = calloc(size, sizeof(int));
	a_x_b_encoded = calloc(size, sizeof(int));			
	a_x_b_decoded = calloc(32, sizeof(int));		

	encode_bitslice((unsigned *) a, (unsigned *) encode_a, size);
	print_binary_array((unsigned *) encode_a, size);
	encode_bitslice((unsigned *) b, (unsigned *) encode_b, size);	

	int carry = 0;
	int overflow = 0;
	signed_add(encode_a, encode_b, &carry, &overflow, size, a_x_b_encoded);
	print_binary_array((unsigned *) a_x_b_encoded, size);
	

	decode_bitslice((unsigned *) a_x_b_encoded, (unsigned *) a_x_b_decoded, size);
	print_binary_array((unsigned *) a_x_b_decoded, size);
	printf("%d\n", a_x_b_decoded[0]);
	printf("%d\n", carry);
	printf("%d\n", overflow);

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