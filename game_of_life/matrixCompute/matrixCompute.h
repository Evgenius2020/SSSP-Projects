#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int squareCompute(int *matrix, int x, int y, int lineSize);
void matrixCompute(int* matrix, int firstLine, int lastLine, int lineSize);