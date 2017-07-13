#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int partReduce(int* data, int length);
int partsReduce(int* results, int length);
int totalReduce(int* matrix, int firstLine, int lastLine, int lineSize);