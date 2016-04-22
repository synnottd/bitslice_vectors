#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <stdio.h>
#include <string.h>	
#include <ctype.h>
#include "arithmetic_integer_operations.h"
//http://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
char * trim(char * str);
char * bitslice_vector_output(unsigned * input, int size, char * name);

#endif
