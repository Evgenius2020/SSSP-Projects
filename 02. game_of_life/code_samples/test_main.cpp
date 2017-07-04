/*
* CPP-14, reduce_parts.cpp
* Purpose: file for testing new code
*
* @author: E.D.
* @version 1.0 04.07.17
*/


#include"prototypes.h"

#include<Windows.h>
#include<iostream>

#define SIZE 3

using namespace std;

void print_matrix(int* matrix, int matrixSize) {
	for (int i = 0; i < matrixSize; i++){
		for (int j = 0; j < matrixSize; j++){
			cout << matrix[i*matrixSize + j];
		}
		cout << endl;
	}
}

void main() {
	int* values = (int*)malloc(sizeof(int)* SIZE*SIZE);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			values[i*SIZE + j] = 0;
		}
	}
	values[0] = 1;
	//values[1] = 1;
	values[3] = 1;
	values[5] = 1;
	values[6] = 1;


	print_matrix(values, SIZE);
	cout << endl;
	cout << "alive: " << total_reduce_sequential(values, SIZE, SIZE, 2) << endl;

	compute_square(values, values, 0, 0, SIZE, SIZE);

	print_matrix(values, SIZE);
	cout << endl;
	cout << "alive: " << total_reduce_sequential(values, SIZE, SIZE, 2) << endl;

	system("pause");
}