#ifndef LOG_SHIFTER_H
#define LOG_SHIFTER_H

#include "circuits.h"
#include "arithmetic_integer_operations.h"
#include "string_helper.h"

void log_left_shifter(unsigned * a, unsigned a_length, unsigned factor_length, unsigned * factor, unsigned result_size);
char * log_left_shifter_output(char * a, unsigned a_length, unsigned factor_length, char * factor);

#endif