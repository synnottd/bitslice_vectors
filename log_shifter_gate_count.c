#include "log_shifter_gate_count.h"

int log_left_shifter(unsigned a_length, unsigned factor_length)
{
	int gate_count = 0;
	unsigned distance = 1;
	for (int i = 0; i < factor_length; i++) {
		for (int j = a_length - 1; j >= 0; j--) {
			if (j < distance) {
				//a[j] = 0 | (a[j] & ~factor[i]);
				gate_count += 3;
			} else {
				//a[j] = ((a[j - distance] & factor[i]) | (a[j] & ~factor[i])); 
				gate_count += 4;
			}
		}
		distance = distance << 1; 
	}
	return gate_count;
}