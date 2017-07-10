#include<iostream>
#include<ctime>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
#include<stdio.h>
#include<cstring>
#include<cstdio>

#define STEPS_LIMIT 10
#define MATRIX_SIZE 10000
#define SOME_DATA_TYPE double
#define NEIGHBORS_NUMBER 8
#define SOURCE_FILE_NAME "data.txt"
#define DATA_TYPE int
#define MPI_DATA_TYPE MPI_INT

using namespace std;

	// ---------- generated reduce ----------

int part_reduce(int* mass, int length) {
	int res = 0;
	for (int i = 0; i < length; i++) {
		if (mass[i]) {
			res++;
		}
	}
        return res;
}

int parts_reduce(int* results, int length) {
	int res = 0;
	for (int i = 0; i < length; i++) {
		res += results[i];
	}
        return res;
}

int total_reduce(int* matrix, int height, int width, int thread) {
	int* rez = (int*)malloc(sizeof(int)*height);
	for (int i = 0; i < height; i++) {
		rez[i] = part_reduce(matrix + (i * width), width);
	}
	return parts_reduce(rez, height);
}

	// ---------- generated calculations ----------
void compute_square(int *matrix, int *buf, int x, int y, int m, int n)
{
	int env[8];
	int rez=0;
	if((y==0)||(x==0)) env[0]=0; else env[0]=matrix[(x-1)*n+y-1];
	if(x==0) env[1]=0; else env[1]=matrix[(x-1)*n+y];
	if((y==n-1)||(x==0)) env[2]=0; else env[2]=matrix[(x-1)*n+y+1];

	if((y==0)) env[3]=0; else env[3]=matrix[x*n+y-1];
	if((y==n-1)) env[4]=0; else env[4]=matrix[x*n+y+1];

	if((y==0)||(x==m-1)) env[5]=0; else env[5]=matrix[(x+1)*n+y-1];
	if(x==m-1) env[7]=0; else env[6]=matrix[(x+1)*n+y];
	if((y==n-1)||(x==m-1)) env[7]=0; else env[7]=matrix[(x+1)*n+y+1];
	for(int i=0;i<8;i++) rez+=env[i];
	if(rez>=3) buf[x*n+y]=1;
	else buf[x*n+y]=0;
}

void step(int *matrix, int width, int heigth) {
	int *bufer = (int*)malloc(sizeof(int) * width * heigth);
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			compute_square(matrix, bufer, i, j, width, heigth);
		}
	}
	for (int i = 0; i < width * heigth; i++) {
		matrix[i] = bufer[i];
	}
	free(bufer);
}

	// ---------- read part of data from file ----------
void read_data(int pid, int processQuantity, int matrixDimension, char* filename, DATA_TYPE* buffer) {
    int blockSize = matrixDimension / processQuantity;
    int begin = pid * blockSize;
    ifstream inputFile;

    inputFile.open(filename);
    string line;
    int i=0, j=0, tmp;

    while(inputFile>>tmp)
    {
        if(i>=pid*blockSize*matrixDimension && i<(pid+1)*blockSize*matrixDimension)
        {   
                buffer[matrixDimension+j]=tmp;
                j++;
        }
        else j=0;
        i++;
    }
    inputFile.close();
}


int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int processQuantity;
    MPI_Comm_size(MPI_COMM_WORLD, &processQuantity);

    // Get the rank of the process
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    int matrixDimension = 4, isLifeExist=0;;
    int blockSize = matrixDimension / processQuantity;
    DATA_TYPE* buffer = new DATA_TYPE [(blockSize+2) * matrixDimension];
    read_data(pid, processQuantity, matrixDimension, "data.txt", buffer);

    for (int lifeStep = 0; lifeStep < STEPS_LIMIT; lifeStep++) {
    // ---------- code for the first process ----------
    if(pid==0)
    {
        MPI_Send(buffer + (blockSize*matrixDimension), matrixDimension, MPI_DATA_TYPE, pid+1, 0, MPI_COMM_WORLD);
        for(int i=0;i<matrixDimension;i++) buffer[i]=0;
        //for(int i=0;i<matrixDimension*(blockSize+2);i++) cout<<buffer[i]<< " ";
        MPI_Recv(buffer+(blockSize+1)*matrixDimension, matrixDimension, MPI_DATA_TYPE, pid+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    }

    // ---------- code for the last process ----------
    if(pid==processQuantity-1)
    {
        MPI_Send(buffer+matrixDimension*1, matrixDimension, MPI_DATA_TYPE, pid-1, 0, MPI_COMM_WORLD);
        for(int i=matrixDimension*(blockSize+1);i<matrixDimension*(blockSize+2);i++) buffer[i]=0;
        MPI_Recv(buffer, matrixDimension, MPI_DATA_TYPE, pid-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    // ---------- code for the other processes ----------
    if(pid!=processQuantity-1 && pid!=0)
    {
        MPI_Send(buffer+matrixDimension*1, matrixDimension, MPI_DATA_TYPE, pid-1, 0, MPI_COMM_WORLD);
        MPI_Send(buffer + (blockSize*matrixDimension), matrixDimension, MPI_DATA_TYPE, pid+1, 0, MPI_COMM_WORLD);
        MPI_Recv(buffer, matrixDimension, MPI_DATA_TYPE, pid-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

	// ---------- code for all processes ----------
    step(buffer, matrixDimension, blockSize + 2);
    int isAnybodyAlive = total_reduce(buffer, matrixDimension, blockSize + 2, 0);
	    
    if(pid == 0) 
    {
        for(int i=0;i<blockSize+2;i++)
	{
		for(int j=0;j<matrixDimension;j++) cout<<buffer[i*matrixDimension+j]<<" ";
		cout<<endl;
	}
    }
	MPI_Allreduce(&isAnybodyAlive,&isLifeExist,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	cout<<isLifeExist<<endl;
	if(!isLifeExist) break;
    }

    delete [] buffer;

    // Finalize the MPI environment.
    MPI_Finalize();

    return 1;
}
