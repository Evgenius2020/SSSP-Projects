#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "matrixCompute.h"
#include "totalReduce.h"

int lifeRun(int steps, int* matrix, int lineSize);