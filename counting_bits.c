#include "counting_bits.h"

char * count_leading_zeros_output(char * a, unsigned length, unsigned exponent_length, char * result)
{
	char * output = malloc(100000); //Create buffer

	int result_size = get_result_length(length - exponent_length) - 1; //The final bit does not need storage until the end
	int storage_used[result_size - 1]; //First/last level doesn't need storage
	for (int i = 0; i < result_size - 1; i++) {
		storage_used[i] = 0;
	}
	char * b, * c, * d;
	b = malloc(sizeof(char) * 100);
	c = malloc(sizeof(char) * 100);
	d = malloc(sizeof(char) * 100);

	sprintf(output, "unsigned a_xor_b, a_xor_b_and_c, a_and_b, carry, mask_0, mask_1;\n");
	sprintf(output + strlen(output), "unsigned * %s = malloc(sizeof(unsigned) * %d);\n", result, result_size * 2); 
	//result has to be bit length of result - 2, first and last bits don't need extra storage    

	int finished, chaining, progress;

	sprintf(output + strlen(output), "mask_1 = %s[%u];\n", a, length - 1);
	sprintf(output + strlen(output), "%s[0] = ~mask_1;\n", result);

	finished = 0;
	chaining = 0;
	progress = 2;

	while (!finished) {
		sprintf(output + strlen(output), "mask_0 = %s[%u] | mask_1;\n", a, length - progress);
		if (length - progress - exponent_length == 0) { //If only 1 and carry left use a half adder and chain and finish
			sprintf(b, "%s[0]", result);
			sprintf(output + strlen(output), "%s", half_adder_output(b, "~mask_0", b, "carry"));
			finished = 1;
		} else {
			sprintf(output + strlen(output), "mask_1 = %s[%d] | mask_0;\n", a, length - progress - 1);
			if (length - progress - exponent_length == 1) {
				finished = 1;
			}
			sprintf(b, "%s[0]", result);
			sprintf(output + strlen(output), "%s", full_adder_output(b, "~mask_0", "~mask_1", b, "carry"));
			progress += 2;
		}
		int level_chaining = 0;
		do {
			switch(storage_used[level_chaining]) {
				case 0: {
					sprintf(output + strlen(output), "%s[%d] = carry;\n", result, level_chaining + 1);
					storage_used[level_chaining]++;
					chaining = 0;
				} break;
				case 1: {
					if (!finished) {
						sprintf(output + strlen(output), "%s[%d] = carry;\n", result, level_chaining + 1 + result_size);
						storage_used[level_chaining]++;
						chaining = 0;
					} else {
						sprintf(d, "%s[%d]", result, level_chaining + 1);
						sprintf(output + strlen(output), "%s", half_adder_output("carry", d, d, "carry"));
						level_chaining++;
						if (level_chaining + 1 == result_size) { 
							finished = 1;
							chaining = 0;
						} else {
							chaining = 1;
						}
					}
				} break;
				case 2: {
					sprintf(d, "%s[%d]", result, level_chaining + 1);
					sprintf(b, "%s[%d]", result, level_chaining + 1 + result_size);
					sprintf(output + strlen(output), "%s", full_adder_output("carry", d, b, d, "carry"));
					storage_used[level_chaining] = 1;
					level_chaining++;
					chaining = 1;

					if (level_chaining + 1 == result_size) { 
						finished = 1;
						chaining = 0;
					}
				} break;
			}
		} while (chaining);
	}
	sprintf(output + strlen(output), "%s[%d] = carry;\n", result, result_size);
	for (int i = result_size + 1; i < result_size * 2; i++) { //Clear temp storage
		sprintf(output + strlen(output), "%s[%d] = 0;\n", result, i);
	}
	return output;
}


void count_leading_zeros(unsigned * a, unsigned length, unsigned exponent_length, unsigned * result)
{
	int result_size = get_result_length(length - exponent_length) - 1; //The final bit does not need storage until the end
	int storage_used[result_size - 1]; //First/last level doesn't need storage
	for (int i = 0; i < result_size - 1; i++) {
		storage_used[i] = 0;
	}
	int finished, chaining, progress;
	unsigned carry, mask_0, mask_1;

	mask_1 = a[length - 1];
	result[0] = ~mask_1;

	finished = 0;
	chaining = 0;
	progress = 2; //Since a[length] does not exist

	while (!finished) {

		mask_0 = a[length - progress] | mask_1;
		if (length - progress - exponent_length == 0) { //If only 1 and carry left use a half adder and chain and finish
			half_adder(result[0], ~mask_0, result, &carry);
			finished = 1;
		} else {
			mask_1 = a[length - progress - 1] | mask_0;
			if (length - progress - exponent_length == 1) {
				finished = 1;
			}
			full_adder(result[0], ~mask_0, ~mask_1, result, &carry);
			progress += 2;
		}
		int level_chaining = 0;
		do {
			switch(storage_used[level_chaining]) {
				case 0: {
					result[level_chaining + 1] = carry;
					storage_used[level_chaining]++;
					chaining = 0;
				} break;
				case 1: {
					if (!finished) {
						result[level_chaining + 1 + result_size] = carry;
						storage_used[level_chaining]++;
						chaining = 0;
					} else {
						half_adder(carry, result[level_chaining + 1], result + level_chaining + 1, &carry);
						level_chaining++;
						if (level_chaining + 1 == result_size) { 
							finished = 1;
							chaining = 0;
						} else {
							chaining = 1;
						}
					}
				} break;
				case 2: { 
					full_adder(carry, result[level_chaining + 1], result[level_chaining + 1 + result_size], 
																result + level_chaining + 1, &carry);
					storage_used[level_chaining] = 1;
					level_chaining++;
					chaining = 1;

					if (level_chaining + 1 == result_size) { 
						finished = 1;
						chaining = 0;
					}
				} break;
				default: {
					for (int i = 0; i < length; i++) { //All ones error
						result[i] = -1;
					}
					return;
				}
			}
		} while (chaining);

	}
	result[result_size] = carry;
	for (int i = result_size + 1; i < length; i++) { //Clear temp storage
		result[i] = 0;
	}
}

void complex_bit_counter(unsigned * a, unsigned length, unsigned * result)
{
	int result_size = get_result_length(length) - 1; //The final bit does not need storage until the end
	int storage_used[result_size - 1]; //First/last level doesn't need storage
	for (int i = 0; i < result_size - 1; i++) {
		storage_used[i] = 0;
	}

	int finished, chaining, progress;
	unsigned carry;
	result[0] = a[0];
	finished = 0;
	chaining = 0;
	progress = 1;
	while (!finished) {
		if (length - progress == 1) { //If only 1 and carry left use a half adder and chain and finish
			half_adder(result[0], a[progress], result, &carry);
			print_binary_array(a+progress, 1);
			print_binary_array(result, 1);
			print_binary_array(&carry,1);
			finished = 1;
		} else {
			if (length - progress == 2) { //If 2 left and carry left use a full adder and chain and finish 
				finished = 1;
			}
			full_adder(result[0], a[progress], a[progress + 1], result, &carry);
			progress += 2;
		}
		int level_chaining = 0;
		do {
			switch(storage_used[level_chaining]) {
				case 0: {
					result[level_chaining + 1] = carry;
					storage_used[level_chaining]++;
					chaining = 0;
				} break;
				case 1: {
					if (!finished) {
						result[level_chaining + 1 + result_size] = carry;
						storage_used[level_chaining]++;
						chaining = 0;
					} else {
						half_adder(carry, result[level_chaining + 1], result + level_chaining + 1, &carry);
						level_chaining++;
						if (level_chaining + 1 == result_size) { 
							finished = 1;
							chaining = 0;
						} else {
							chaining = 1;
						}
					}

				} break;
				case 2: { 
					full_adder(carry, result[level_chaining + 1], result[level_chaining + 1 + result_size], 
																result + level_chaining + 1, &carry);
					storage_used[level_chaining] = 1;
					level_chaining++;
					chaining = 1;

					if (level_chaining + 1 == result_size) { 
						finished = 1;
						chaining = 0;
					}
				} break;
				default: {
					for (int i = 0; i < length; i++) { //All ones error
						result[i] = -1;
					}
					return;
				}
			}
		} while (chaining);
	}
	result[result_size] = carry;
	for (int i = result_size + 1; i < length; i++) { //Clear temp storage
		result[i] = 0;
	}
}

char * complex_bit_counter_output(char * a, unsigned length, char * result)
{
	char * output = malloc(100000); //Create buffer

	int result_size = get_result_length(length) - 1; //The final bit does not need storage until the end
	int storage_used[result_size - 1]; //First/last level doesn't need storage
	for (int i = 0; i < result_size - 1; i++) {
		storage_used[i] = 0;
	}
	char * b, * c, * d;
	b = malloc(sizeof(char) * 100);
	c = malloc(sizeof(char) * 100);
	d = malloc(sizeof(char) * 100);

	sprintf(output, "unsigned a_xor_b, a_xor_b_and_c, a_and_b, temp, carry;\n");
	sprintf(output + strlen(output), "unsigned * %s = malloc(sizeof(unsigned) * %d);\n", result, result_size * 2); 
	//result has to be bit length of result - 2, first and last bits don't need extra storage    

	int finished, chaining, progress;
	unsigned carry;
	sprintf(output + strlen(output), "%s[0] = %s[0];\n", result, a);
	finished = 0;
	chaining = 0;
	progress = 1;
	

	while (!finished) {
		if (length - progress == 1) { //If only 1 and carry left use a half adder and chain and finish
			sprintf(d, "%s[0]", result);
			sprintf(b, "%s[%d]", a, progress);
			sprintf(output + strlen(output), "%s", half_adder_output(d, b, d, "carry"));
			finished = 1;
		} else {
			if (length - progress == 2) { //If 2 left and carry left use a full adder and chain and finish 
				finished = 1;
			}
			sprintf(d, "%s[0]", result);
			sprintf(b, "%s[%d]", a, progress);
			sprintf(c, "%s[%d]", a, progress + 1);
			sprintf(output + strlen(output), "%s", full_adder_output(d, b, c, d, "carry"));
			progress += 2;
		}
		int level_chaining = 0;
		do {
			switch(storage_used[level_chaining]) {
				case 0: {
					sprintf(output + strlen(output), "%s[%d] = carry;\n", result, level_chaining + 1);
					storage_used[level_chaining]++;
					chaining = 0;
				} break;
				case 1: {
					if (!finished) {
						sprintf(output + strlen(output), "%s[%d] = carry;\n", result, level_chaining + 1 + result_size);
						storage_used[level_chaining]++;
						chaining = 0;
					} else {
						sprintf(d, "%s[%d]", result, level_chaining + 1);
						sprintf(output + strlen(output), "%s", half_adder_output("carry", d, d, "carry"));
						level_chaining++;
						if (level_chaining + 1 == result_size) { 
							finished = 1;
							chaining = 0;
						} else {
							chaining = 1;
						}
					}

				} break;
				case 2: {
					sprintf(d, "%s[%d]", result, level_chaining + 1);
					sprintf(b, "%s[%d]", result, level_chaining + 1 + result_size);
					sprintf(output + strlen(output), "%s", full_adder_output("carry", d, b, d, "carry"));
					storage_used[level_chaining] = 1;
					level_chaining++;
					chaining = 1;

					if (level_chaining + 1 == result_size) { 
						finished = 1;
						chaining = 0;
					}
				} break;
			}
		} while (chaining);
	}
	sprintf(output + strlen(output), "%s[%d] = carry;\n", result, result_size);
	for (int i = result_size + 1; i < length; i++) { //Clear temp storage
		sprintf(output + strlen(output), "%s[%d] = 0;\n", result, i);
	}
	return output;
}

unsigned get_result_length (unsigned full_length) {
	unsigned power = 1;
	unsigned length = 1;
	while (full_length > power) {
		length++;
		full_length -= power;
		power = power << 1;
	}
	return length;
}

void state_based_leading_zero(unsigned * input, unsigned length, unsigned exponent_length, unsigned * result)
{
	int result_length = 1;
	for (int i = 1; i < exponent_length; i++) {
		result_length = result_length << 1;
	}


	unsigned mask = 0;
	unsigned count = 1;
	int twos;
	for (int i = length - 1; i >= (int) length - result_length; i--) {
		mask |= input[i];
		result[0] ^= ~mask;
		twos = 2;
		for (int j = 1; j < result_length; j++){
			if (count % twos == 0) {
				result[j] ^= ~mask;
 			}
 			twos = twos << 1;
		}
		count++; 	
	}
}

char * state_based_leading_zero_output(char * input, unsigned length, unsigned exponent_length, char * result)
{
	char * output = malloc(sizeof(char) * 100000);
	int result_length = 1;
	for (int i = 1; i < exponent_length; i++) {
		result_length = result_length << 1;
	}


	unsigned mask = 0;
	unsigned count = 1;
	int twos;
	sprintf(output, "unsigned mask = 0;\n");


	for (int i = length - 1; i >= (int) length - result_length; i--) {
		sprintf(output + strlen(output), "mask |= %s[%d];\n", input, i);
		sprintf(output + strlen(output), "%s[0] ^= ~mask;\n", result);
		twos = 2;
		for (int j = 1; j < result_length; j++){
			if (count % twos == 0) {
				sprintf(output + strlen(output), "%s[%d] ^= ~mask;\n", result, j);
 			}
 			twos = twos << 1;
		}
		count++; 	
	}

	return trim(output);
}

void naive_bit_counter(unsigned * input, unsigned length, unsigned * result) 
{
	full_adder(input[0], input[1], input[2], result, result + 1);
	unsigned carry;
	unsigned count = 1;
	unsigned current_max_length = 2;
	unsigned current_overflow_value = 4;
	for (int i = 3; i < length; i += 2) {
		if (i + 1 == length) {
			half_adder(result[0], input[i], result, &carry);
		} else {
			full_adder(result[0], input[i], input[i + 1], result, &carry);
		}
		if (current_max_length <= i) {
			current_overflow_value = current_overflow_value << 1;
			current_max_length++;
		}
		for (int j = 1; j < current_max_length - 1; j++) {
			half_adder(result[j], carry, result + j, &carry);
		}
		result[current_max_length - 1] = carry | result[current_max_length - 1];
	}
}



