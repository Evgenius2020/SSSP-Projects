#include<fstream>
#include<stdlib.h>

#define MATRIX_SIZE 10
#define DATA_TYPE int

using namespace std;


int main() {
    ofstream outputFile;

    outputFile.open("data.txt");

    DATA_TYPE value = 1;
    for (int y = 0; y < MATRIX_SIZE; y++) {
        for (int x = 0; x < MATRIX_SIZE; x++) {
            //outputFile.write((char*)&value, sizeof(DATA_TYPE));
            outputFile<<value<<" ";
        }
        outputFile << endl;
    }
    outputFile.close();
    return 0;
}
