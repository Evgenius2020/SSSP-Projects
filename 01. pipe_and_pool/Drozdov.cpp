/**
*	main.cpp
*	Purpose: implementation of the POOL and PIPE functions
*
*	@author Eduard Drozdov
*	@version 1.0 03/07/17
*/


#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include<Windows.h>

#include "threads_example.h"


using namespace std;

void generatePool(vector<string> filenames){
	ofstream outputFile;
	outputFile.open("pool.txt");

	// create basic functions
	for (int i = 0; i < filenames.size(); i++) {
		outputFile << "int "; // create function head
		outputFile << filenames[i].substr(0, filenames[i].length() - 4); // cut off ".txt" file extension
		outputFile << "(int arg)\n";
		fstream currentFunctionFile;
		currentFunctionFile.open(filenames[i]);
		char symbol;
		while (currentFunctionFile.get(symbol)) // copy function body
			outputFile << symbol;
		currentFunctionFile.close();
		outputFile << "\n\n";
	}

	// create POOL function
	outputFile << "int pool(vector<int> args)\n{\n"; // create function head
	// create function body
	for (int i = 0; i < filenames.size(); i++) {
		outputFile << "\t";
		outputFile << filenames[i].substr(0, filenames[i].length() - 4); // cut off ".txt" file extension
		outputFile << "(arg[" << i << "]);\n";
	}

	outputFile << "}";
	outputFile.close();
};

void generatePoolThreads(vector<string> filenames){
	ofstream outputFile;
	outputFile.open("pool.txt");

	outputFile << "#define THREAD_NUMBER 10\n";
	// create basic functions
	for (int i = 0; i < filenames.size(); i++) {
		outputFile << "int "; // create function head
		outputFile << filenames[i].substr(0, filenames[i].length() - 4); // cut off ".txt" file extension
		outputFile << "(int arg)\n";
		fstream currentFunctionFile;
		currentFunctionFile.open(filenames[i]);
		char symbol;
		while (currentFunctionFile.get(symbol)) // copy function body
			outputFile << symbol;
		currentFunctionFile.close();
		outputFile << "\n\n";
	}

	// create POOL function
	outputFile << "int pool(vector<int> args)\n{\n"; // create function head

	// create function body
	outputFile << "\t" << "thread* t[THREAD_NUMBER];\n";
	for (int i = 0; i < filenames.size(); i++) {
		outputFile << "\t";
		outputFile << "t[" << i << "] = new thread(";
		outputFile << filenames[i].substr(0, filenames[i].length() - 4); // cut off ".txt" file extension
		outputFile << ", " << "arg[" << i << "]);\n";
	}

	for (int i = 0; i < filenames.size(); i++) {
		outputFile << "\t";
		outputFile << "t[" << i << "]->join();\n";
	}

	outputFile << "}";
	outputFile.close();
};

void generatePipe(vector<string> filenames){
	ofstream outputFile;
	outputFile.open("pipe.txt");

	// create basic functions
	for (int i = 0; i < filenames.size(); i++) {
		outputFile << "int "; // create function head
		outputFile << filenames[i].substr(0, filenames[i].length() - 4); // cut off ".txt" file extension
		outputFile << "(int arg)\n";
		fstream currentFunctionFile;
		currentFunctionFile.open(filenames[i]);
		char symbol;
		while (currentFunctionFile.get(symbol)) // copy function body
			outputFile << symbol;
		currentFunctionFile.close();
		outputFile << "\n\n";
	}

	// create PIPE function
	outputFile << "int pipe(int arg)\n{\n"; // create function head
	// create function body
	outputFile << "\t";
	for (int i = filenames.size() - 1; i >= 0; i--) {
		outputFile << filenames[i].substr(0, filenames[i].length() - 4) << "("; // cut off ".txt" file extension
	}
	outputFile << "arg";
	for (int i = 0; i < filenames.size(); i++)
		outputFile << ")";
	outputFile << ";";
	outputFile << "\n";
	outputFile << "}";

	outputFile.close();	
};


void main(){
	//generatePipe({ "function1.txt", "function2.txt", "function15.txt" });
	//generatePool({ "function1.txt", "function2.txt", "function15.txt" });
	generatePoolThreads({ "function1.txt", "function2.txt", "function15.txt" });
	//runAllThreads();
	//system("pause");
}

