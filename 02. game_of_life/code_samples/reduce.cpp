/*
* CPP-14, reduce_parts.cpp
* Purpose: implementation of the reduce_parts function
*
* @author: E.D.
* @version 1.0 04.07.17
*/


#include"prototypes.h"


#define DATA_TYPE int


DATA_TYPE reduce_parts(DATA_TYPE* values, int valuesNumber) {
	int rez = 0;
	for (int i = 0; i < valuesNumber; i++)
	{
		rez += values[i];
	}
	return rez;
}


bool reduce_parts_bool(DATA_TYPE* values, int valuesNumber) {
	for (int i = 0; i < valuesNumber; i++) {
		if (values[i]) return true;
	}
	return false;
}


DATA_TYPE part_reduce(DATA_TYPE* matrix, int length)
{
	int rez = 0;
	for (int i = 0; i < length; i++)
	{
		if(matrix[i]) rez ++;
	}
	return rez;
}