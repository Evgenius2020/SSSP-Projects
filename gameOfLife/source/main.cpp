#include "lifeRun.h"

int main(int argc, char* argv[]) {
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
        return 0;
}
