#include "matrixCompute.h"

void matrixCompute(int* matrix, int *firstLine, int *lastLine, int lineSize) {
	int bufSize = (*lastLine - *firstLine + 1) * lineSize;
	int* buf = (int*)malloc(sizeof(int) * bufSize);
	for (int i = 0; i < bufSize; i++) {
		buf[i] = squareCompute(matrix, i % lineSize, *firstLine + (i / lineSize), lineSize);
	}
	for (int i = 0; i < bufSize; i++) {
		matrix[*firstLine * lineSize + i] = buf[i];
	}
}