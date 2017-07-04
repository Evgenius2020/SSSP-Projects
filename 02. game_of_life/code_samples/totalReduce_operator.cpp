/*
* CPP-14, .cpp
* Purpose: generate total_reduce function
*
* @author: team
* @version 1.0 04.07.17
*/


#include"prototypes.h"

#include<stdlib.h>


int total_reduce_sequential(int* matrix, int height, int width, int threads) {
	int* rez = (int*)malloc(sizeof(int)*height);
	for (int i = 0; i < height; i++) {
		rez[i] = part_reduce(matrix + (i * width), width);
	}
	return reduce_parts(rez, height);
}


int total_reduce(int* matrix, int height, int width, int threads) {
	int* rez = (int*)malloc(sizeof(int)*height);
	for (int i = 0; i < height; i++) {
		rez[i] = part_reduce(matrix + (i * width), width);
	}
	return reduce_parts(rez, height);
}