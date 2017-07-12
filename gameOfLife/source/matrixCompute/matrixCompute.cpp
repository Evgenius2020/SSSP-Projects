#include "matrixCompute.h"

void matrixCompute(int* matrix, int firstLine, int lastLine, int lineSize) {
	for (int y = firstLine; y <= lastLine; y++) {
		for (int x = 0; x < lineSize; x++) {
			matrix[y * lineSize + x] = squareCompute(matrix, x, y, lineSize);
		}
	}
}