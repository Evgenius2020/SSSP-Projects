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

int lifeRun(int steps, int* data, int lineSize) {
	int commRank, commSize;
	MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	int firstLine, lastLine;
	findBeginEnd(&firstLine, &lastLine, commSize, commRank, lineSize);
	while ((steps) && (totalReduce(data, firstLine, lastLine, lineSize))) {
		if (firstLine != 0) {
			MPI_Send(data + (firstLine*lineSize), lineSize, MPI_INT, commRank - 1, 0, MPI_COMM_WORLD);
			MPI_Recv(data + ((firstLine - 1)*lineSize), lineSize, MPI_INT, commRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		if (lastLine != lineSize - 1) {
			MPI_Send(data + (lastLine*lineSize), lineSize, MPI_INT, commRank + 1, 0, MPI_COMM_WORLD);
			MPI_Recv(data + ((lastLine + 1)*lineSize), lineSize, MPI_INT, commRank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		compute_matrix(data, firstLine, lastLine, lineSize);
		steps--;
	}
	int startIndex, endIndex;
	if (commRank) {
		startIndex = firstLine * lineSize;
		endIndex = (lastLine + 1) * lineSize - 1;
		MPI_Send(&startIndex, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&endIndex, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(data + startIndex, endIndex - startIndex + 1, MPI_INT, 0, commRank, MPI_COMM_WORLD);
		printf("#%d: Sent data[%d..%d]: ", commRank, startIndex, endIndex);
		for (int i = startIndex; i <= endIndex; i++) {
			printf("%d ", data[i]);
		}
		printf("\n");
		fflush(stdout);
	}
	else {
		for (int i = 1; i < commSize; i++) {
			MPI_Recv(&startIndex, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&endIndex, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(data + startIndex, endIndex - startIndex + 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("#0: Received data from #%d[%d..%d]: ", i, startIndex, endIndex);
			for (int i = startIndex; i <= endIndex; i++) {
				printf("%d ", data[i]);
			}
			printf("\n");
			fflush(stdout);
		}
	}
	return steps;
}

void main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int commRank, commSize;
	MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	int steps = atoi(argv[1]);
	int lineSize = atoi(argv[2]);
	int* data = (int*)malloc(sizeof(int) * lineSize * lineSize);
	FILE* in = fopen(argv[3], "r");
	for (int i = 0; i < lineSize * lineSize; i++) {
		while (i < lineSize * lineSize) {
			fscanf(in, "%d ", &data[i]);
			i++;
		}
	}
	fclose(in);

	steps = lifeRun(steps, data, lineSize);

	if (commRank == 0) {
		FILE* out = fopen(argv[4], "w");
		fprintf(out, "%d\n", steps);
		for (int y = 0; y < lineSize; y++) {
			for (int x = 0; x < lineSize; x++) {
				fprintf(out, "%d ", data[y*lineSize + x]);
			}
			fprintf(out, "\n");
		}
		fclose(out);
	}
	free(data);
	MPI_Finalize();
}