#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int part_reduce(int* matrix, int length)
{
	int rez = 0;
	for(int i = 0; i < length; i++)
	{
		rez+=matrix[i];
	}
	return rez;
}

int main(int argc, char *argv[])
{
	ifstream in;
	in.open(argv[1]);
	int size, rez;
	in>>size;		
	int * matrix = (int*)malloc(sizeof(int)*(size));
	
	for(int i = 0; i < size; i++)
	{
		in>>matrix[i];
		//printf("%d\n",matrix[i]);	
	}
	rez=part_reduce(matrix, size);
	printf("%d\n",rez);
	free(matrix);
	in.close();
	return 0;
}
