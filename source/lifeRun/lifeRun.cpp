#include "lifeRun.h"

void findBeginEnd(int *firstLine, int *lastLine, int commSize, int commRank, int height) {
	int linesPerProcess = height / commSize;
	int mod = height % commSize;
	if (commRank < mod) {
		*firstLine = (linesPerProcess+1)*commRank;
		*lastLine = (linesPerProcess+1)*(1 + commRank)-1;
	}
	else {
		*firstLine = (linesPerProcess+1)*mod+linesPerProcess*(commRank-mod);
		*lastLine = (linesPerProcess+1)*mod+linesPerProcess*(commRank+1-mod)-1;
	}
}

int lifeRun(int steps, int* matrix, int lineSize) {
	int commRank, commSize;
	MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	int firstLine, lastLine;
	findBeginEnd(&firstLine, &lastLine, commSize, commRank, lineSize);
	while ((steps) && (totalReduce(matrix, firstLine, lastLine, lineSize))) {
		if (firstLine != 0) {
			MPI_Send(matrix + (firstLine*lineSize), lineSize, MPI_INT, commRank - 1, 0, MPI_COMM_WORLD);
			MPI_Recv(matrix + ((firstLine - 1)*lineSize), lineSize, MPI_INT, commRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		if (lastLine != lineSize - 1) {
			MPI_Send(matrix + (lastLine*lineSize), lineSize, MPI_INT, commRank + 1, 0, MPI_COMM_WORLD);
			MPI_Recv(matrix + ((lastLine + 1)*lineSize), lineSize, MPI_INT, commRank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		matrixCompute(matrix, &firstLine, &lastLine, lineSize);
		steps--;
	}
	int startIndex, endIndex;
	if (commRank) {
		startIndex = firstLine * lineSize;
		endIndex = (lastLine + 1) * lineSize - 1;
		MPI_Send(&startIndex, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&endIndex, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(matrix + startIndex, endIndex - startIndex + 1, MPI_INT, 0, commRank, MPI_COMM_WORLD);
	}
	else {
		for (int i = 1; i < commSize; i++) {
			MPI_Recv(&startIndex, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&endIndex, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(matrix + startIndex, endIndex - startIndex + 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			fflush(stdout);
		}
	}
	return steps;
}
