#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "totalReduce.h"
#include "matrixCompute.h"

int lifeRun(int steps, int* matrix, int lineSize);