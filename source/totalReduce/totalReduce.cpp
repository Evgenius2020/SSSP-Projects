#include "totalReduce.h"

int totalReduce(int* matrix, int firstLine, int lastLine, int lineSize) {
	int aliveGlobalCount, aliveLocalCount;
	int parts = lastLine - firstLine + 1;
	int* partResults = (int*)malloc(parts * sizeof(int));

	for (int y = firstLine; y <= lastLine; y++) {
		partResults[y - firstLine] = partReduce(matrix + (y*lineSize), lineSize);
	}
	aliveLocalCount = partsReduce(partResults, parts);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Allreduce(&aliveLocalCount, &aliveGlobalCount, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	free(partResults);
	return aliveGlobalCount;
}
