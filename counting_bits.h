#ifndef COUNTING_BITS_H
#define COUNTING_BITS_H

#include "circuits.h"
#include "arithmetic_integer_operations.h"
#include <math.h>



void simple_bit_counter(unsigned * a, unsigned length, unsigned * result);
char * simple_bit_counter_output(unsigned length, char * var_names[]);
void complex_bit_counter(unsigned * a, unsigned length, unsigned * result);
unsigned get_result_length (unsigned full_length);
char * complex_bit_counter_output(char * a, unsigned length, char * result);
void count_leading_zeros(unsigned * a, unsigned length, unsigned exponent_length, unsigned * result);
char * count_leading_zeros_output(char * a, unsigned length, unsigned exponent_length, char * result);
void state_based_leading_zero(unsigned * input, unsigned length, unsigned exponent_length, unsigned * result);
char * state_based_leading_zero_output(char * input, unsigned length, unsigned exponent_length, char * result);
void naive_bit_counter(unsigned * input, unsigned length, unsigned * result);

#endif