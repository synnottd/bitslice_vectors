#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_helper.h"

void half_adder(unsigned a, unsigned b, unsigned * result, unsigned * carry);
char * half_adder_output(char * a, char * b, char * result, char * carry);
void full_adder(unsigned a, unsigned b, unsigned c, unsigned * result, unsigned * carry);
char * full_adder_output(char * a, char * b, char * c, char * result, char * carry);

#endif