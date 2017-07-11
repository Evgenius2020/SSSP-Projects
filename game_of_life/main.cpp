#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int partReduce(int* mass, int length) {
	int res = 0;
	for (int i = 0; i < length; i++) {
		if (mass[i]) {
			res++;
		}
	}
	return res;
}

int partsReduce(int* results, int length) {
	int res = 0;
	for (int i = 0; i < length; i++) {
		res += results[i];
	}
	return res;
}

int totalReduce(int* data, int firstLine, int lastLine, int lineSize) {
	int aliveGlobalCount, aliveLocalCount;
	int parts = lastLine - firstLine + 1;
	int* partResults = (int*)malloc(parts * sizeof(int));

	for (int y = firstLine; y <= lastLine; y++) {
		partResults[y - firstLine] = partReduce(data + (y*lineSize), lineSize);
	}
	aliveLocalCount = partsReduce(partResults, parts);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Allreduce(&aliveLocalCount, &aliveGlobalCount, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	free(partResults);
	return aliveGlobalCount;
}

int compute_square(int *matrix, int x, int y, int lineSize) {
	int dirx[8] = { 0,  1,  1,  1,  0, -1, -1,  -1 };
	int diry[8] = { -1, -1,  0,  1,  1,  1,  0,  -1 };
	int neighbours = 0;
	for (int i = 0; i < 8; i++) {
		int neighbourX = x + dirx[i];
		int neighbourY = y + diry[i];
		if ((neighbourX >= 0) && (neighbourX < lineSize)
			&& (neighbourY >= 0) && (neighbourY < lineSize)) {
			if (matrix[neighbourY * lineSize + neighbourX]) {
				neighbours++;
			}
		}
	}

	// Game specific.
	if (matrix[y * lineSize + x]) {
		return ((neighbours == 2) || (neighbours == 3)) ? 1 : 0;
	}
	else {
		return (neighbours == 3) ? 1 : 0;
	}
}

void compute_matrix(int* data, int firstLine, int lastLine, int lineSize) {
	for (int y = firstLine; y <= lastLine; y++) {
		for (int x = 0; x < lineSize; x++) {
			data[y * lineSize + x] = compute_square(data, x, y, lineSize);
		}
	}
}

void findBeginEnd(int *firstLine, int *lastLine, int commSize, int commRank, int height) {
	int linesPerProcess = height / commSize;
	int mod = height % commSize;

	if (commRank < mod) {
		*firstLine = linesPerProcess*commRank * 2;
		*lastLine = linesPerProcess*(1 + commRank * 2);
	}
	else {
		*firstLine = linesPerProcess*(commRank + mod);
		*lastLine = linesPerProcess*(1 + commRank + mod) - 1;
	}
}

void lifeRun(int steps, int* data, int lineSize) {
	int commRank, commSize;
	MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	int firstLine, lastLine;
	findBeginEnd(&firstLine, &lastLine, commSize, commRank, lineSize);
	
	for (int i = 0; i < commSize; i++) {
		MPI_Barrier(MPI_COMM_WORLD);
		if (commRank == i) {
			printf("#%d: Local data\n", commRank);
			for (int y = firstLine; y <= lastLine; y++) {
				for (int x = 0; x < lineSize; x++) {
					printf("%d ", data[y*lineSize + x]);
				}
				printf("\n");
			}
		}
		fflush(stdout);
	}

	while ((steps) && (totalReduce(data, firstLine, lastLine, lineSize))) {
		compute_matrix(data, firstLine, lastLine, lineSize);
		steps--;
	}
}

void main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int commRank;
	MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
	printf("#%d: Started\n", commRank);
	fflush(stdout);
	int steps = atoi(argv[1]);
	int lineSize = atoi(argv[2]);
	int* data = (int*)malloc(sizeof(int) * lineSize * lineSize);
	FILE* in = fopen(argv[3], "r");
	int i = 0;
	while (i < lineSize*lineSize) {
		fscanf(in, "%d ", &data[i]);
		i++;
	}
	fclose(in);
	printf("#%d: Successfully initailized\n", commRank);
	fflush(stdout);

	lifeRun(steps, data, lineSize);

	free(data);
	MPI_Finalize();
}