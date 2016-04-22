build:
	gcc arithmetic_integer_operations.c circuits.c counting_bits.c main.c string_helper.c log_shifter.c -o bitslice

output: 
	gcc arithmetic_integer_operations.c circuits.c counting_bits.c output.c string_helper.c log_shifter.c -o output