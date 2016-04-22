#include "log_shifter.h"

void log_left_shifter(unsigned * a, unsigned a_length, unsigned factor_length, unsigned * factor, unsigned result_size)
{
	unsigned distance = 1;
	for (int i = 0; i < factor_length; i++) {
		for (int j = a_length - 1; j >= 0; j--) {
			if (j < distance) {
				a[j] = 0 | (a[j] & ~factor[i]);
			} else {
				a[j] = ((a[j - distance] & factor[i]) | (a[j] & ~factor[i])); 
			}
		}
		distance = distance << 1; 
	}
}

char * log_left_shifter_output(char * a, unsigned a_length, unsigned factor_length, char * factor)
{
	char * output = malloc(sizeof(char) * 100000);
	unsigned distance = 1;

	for (int i = 0; i < factor_length; i++) {
		for (int j = a_length - 1; j >= 0; j--) {
			if (j < distance) {
				sprintf(output + strlen(output), "%s[%d] = 0 | (%s[%d] & ~%s[%d]);\n", a, j, a, j, factor, i);

			} else {
				sprintf(output + strlen(output), "%s[%d] = (%s[%d] & %s[%d]) | (%s[%d] & ~%s[%d]);\n", 
															a, j, a, j - distance, factor, i, a, j, factor, i);
			}
		}	
		distance = distance << 1;
	}
	return trim(output);
}

