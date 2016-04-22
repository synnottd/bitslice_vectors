#include "circuits.h"

void half_adder(unsigned a, unsigned b, unsigned * result, unsigned * carry)
{
	unsigned temp = a ^ b;
	*carry = a & b;
	*result = temp;
}

char * half_adder_output(char * a, char * b, char * result, char * carry)
{
	char * output = malloc(sizeof(char) * 1000);
	sprintf(output, "temp = %s ^ %s;\n", a, b);
	sprintf(output + strlen(output), "%s = %s & %s;\n", carry, a, b);
	sprintf(output + strlen(output), "%s = temp;\n", result);
	output = trim(output);
	return output;
}

void full_adder(unsigned a, unsigned b, unsigned c, unsigned * result, unsigned * carry)
{
	unsigned a_xor_b, a_xor_b_and_c, a_and_b; 
	a_and_b = a & b;
	a_xor_b = a ^ b;
	a_xor_b_and_c = a_xor_b & c;
	*result = a_xor_b ^ c;
	*carry = a_xor_b_and_c | a_and_b;
}

char * full_adder_output(char * a, char * b, char * c, char * result, char * carry)
{ //Assumes unsigned a_xor_b, a_xor_b_and_c, a_and_b; declared
	char * output = malloc(sizeof(char) * 1000);
	sprintf(output, "a_and_b = %s & %s;\n", a, b);
	sprintf(output + strlen(output), "a_xor_b = %s ^ %s;\n", a, b);
	sprintf(output + strlen(output), "a_xor_b_and_c = a_xor_b & %s;\n", c);
	sprintf(output + strlen(output), "%s = a_xor_b ^ %s;\n", result, c);
	sprintf(output + strlen(output), "%s = a_xor_b_and_c | a_and_b;\n", carry);
	output = trim(output);
	return output;
}	