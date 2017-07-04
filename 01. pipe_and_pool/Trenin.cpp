#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	string str; 
	string line;
	ifstream in;
	ofstream out;

	for(int i =1; i< argc; i++)
	{
		in.open(argv[i]);
		str+="int ";
		for(int j=0; j<strlen(argv[i]); j++)
		{
			if(argv[i][j] == '.') break;
			str+=argv[i][j];
		}
		str+="(int arg)";
		while ( getline (in,line) )
		{
			str+="\n";
			str+=line;
		}
		str+="\n";	
		str+="\n";	
		in.close();
		
	}
	
	str+="int pipe(int arg)";
	str+="\n";
	str+="{";	
	str+="\n";
	str+="return ";
	for(int i =1; i< argc; i++)
	{
		for(int j=0; j<strlen(argv[i]); j++)
		{
			if(argv[i][j] == '.') break;
			str+=argv[i][j];
		}
		str+="(";
	}
	str+="arg";
	for(int i =1; i< argc; i++) str+=")";
	str+=";";
	str+="\n";
	str+="}";	
	str+="\n";
	

	out.open("output.txt");	
	out<<str<<endl;
	out.close();	
	return 0;
}
