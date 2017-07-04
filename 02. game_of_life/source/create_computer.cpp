#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

/*Входные данные - ф-я F, используемая в compute_square и сама compute_square(точнее одноимёные файлы с ними)*/

int main(int argc, char* argv[])
{
	string str;
	string line; 
	ifstream in;
	ofstream out;
	out.open("output.cpp");
	for(int i = 1 ; i < argc; i++)
	{
		in.open(argv[i]);
		while ( getline (in,line) )
		{
			str+="\n";
			str+=line;
		}
		str+="\n";	
		str+="\n";	
		in.close();
	}

	str+="void step(int *matrix, int m, int n)\n";
	str+="{\n";
	str+="	int *bufer = (int*)malloc(sizeof(int)*size*size);\n";
	str+="	for(int i = 0; i < size; i++)\n";
	str+="	{\n";
	str+="		for(int j = 0; j < size; j++)\n";
	str+="			compute_square(matrix, bufer, i, j, m, n);\n";
	str+="	}\n";
	str+="	for(int i = 0; i < size * size; i++) matrix[i]=bufer[i];\n";
	str+="	free(bufer);\n";
	str+="}\n";
	out<<str;
	out.close();
	return 0;
}
