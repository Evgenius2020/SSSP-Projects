#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "matrixCompute\matrixCompute.h"
#include "totalReduce\totalReduce.h"

int lifeRun(int steps, int* matrix, int lineSize);