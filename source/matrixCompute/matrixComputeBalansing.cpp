#include "matrixCompute.h"
#include "totalReduce.h"

void matrixCompute(int* matrix, int *firstLine, int *lastLine, int lineSize) {
	int topLife = 0, bottomLife = 0, myLife = 0, topFlag = 0, bottomFlag = 0;
	int commRank;	
	MPI_Comm_rank(MPI_COMM_WORLD, &commRank);

	myLife = totalReduce(matrix, *firstLine, *lastLine, lineSize);

	if (*firstLine != 0) {
		MPI_Send(&myLife, 1, MPI_INT, commRank - 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&topLife, 1, MPI_INT, commRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	if (*lastLine != lineSize - 1) {
		MPI_Send(&myLife, 1, MPI_INT, commRank + 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&bottomLife, 1, MPI_INT, commRank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	if (*firstLine == 0) topLife = myLife;
	if (*lastLine == lineSize - 1) bottomLife = myLife;

	if (myLife > topLife)
	{
		*firstLine -= 1;
		topFlag++;
	}
	if (myLife > bottomLife)
	{
		*lastLine += 1;
		bottomFlag++;
	}

	if (*firstLine != 0 && topFlag != 0)
	{
		MPI_Send(matrix + ((*firstLine)*lineSize), lineSize, MPI_INT, commRank - 1, 0, MPI_COMM_WORLD);
		MPI_Recv(matrix + (((*firstLine) - 1)*lineSize), lineSize, MPI_INT, commRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	if (*lastLine != lineSize - 1 && bottomFlag != 0)
	{
		MPI_Send(matrix + ((*lastLine)*lineSize), lineSize, MPI_INT, commRank + 1, 0, MPI_COMM_WORLD);
		MPI_Recv(matrix + (((*lastLine) + 1)*lineSize), lineSize, MPI_INT, commRank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	

	int bufSize = (*lastLine - *firstLine + 1) * lineSize;
	int* buf = (int*)malloc(sizeof(int) * bufSize);
	for (int i = 0; i < bufSize; i++) {
		buf[i] = squareCompute(matrix, i % lineSize, *firstLine + (i / lineSize), lineSize);
	}
	for (int i = 0; i < bufSize; i++) {
		matrix[*firstLine * lineSize + i] = buf[i];
	}
}
