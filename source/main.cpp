#include "lifeRun.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	int commRank, commSize;	
	double startwtime = 0.0;
  	double endwtime; 		
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	if (commRank == 0) 
  	{ 
    	startwtime = MPI_Wtime();
  	}
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
	if (commRank == 0)
  	{   
    	endwtime = MPI_Wtime();
    	cout << (endwtime-startwtime)*1000 << endl;      
  	}
	free(data);
	MPI_Finalize();
	return 0;
}
