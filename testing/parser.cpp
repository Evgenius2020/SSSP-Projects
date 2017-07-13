/*
 * Input: name of the test file and folder for output files
 *
 * Output: flow of the test data in following order:
 * 	number of process, steps limit, matrix height, 
 * 	matrix width, input matrix, output matrix.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    fstream inputFile;
    inputFile.open(argv[1]);
    line = " ";
    while (line != "END OF DESCRIPTION")
        getline(inputFile, line);

    getline(inputFile, line);
    while (line[0] != ':')
        line.erase(0, 1);
    line.erase(0, 1); // delete column and space before value
    stringstream stream(line);
    int processesNumber;
    stream >> processesNumber;

    getline(inputFile, line);
    while (line[0] != ':')
        line.erase(0, 1);
    line.erase(0, 1); // delete column and space before value
    int stepsLimit;
    stringstream stream2(line);
    stream2 >> stepsLimit;

    getline(inputFile, line);
    while (line[0] != ':')
        line.erase(0, 1);
    line.erase(0, 1); // delete column and space before value
    int height;
    stringstream stream3(line);
    stream3 >> height;

    int width;
    stream3 >> width;

    int **inputMatrix = new int *[height];
    for (int i = 0; i < height; i++)
        inputMatrix[i] = new int[width];

    for (int i = 0; i < height; i++)
    {
        getline(inputFile, line);
        string delimiter = " ";
        string value;
        for (int j = 0; j < width; j++)
        {
            value = line.substr(0, line.find(delimiter));
            inputMatrix[i][j] = stoi(value);
            line.erase(0, line.find(delimiter) + delimiter.length());
        }
    }
    getline(inputFile, line);
    getline(inputFile, line);
    while (line[0] != ':')
        line.erase(0, 1);
    line.erase(0, 1); // delete column and space before value
    int expectedSteps;
    stringstream stream4(line);
    stream4 >> expectedSteps;
    getline(inputFile, line);

    int **expectedMatrix = new int *[height];
    for (int i = 0; i < height; i++)
        expectedMatrix[i] = new int[width];

    for (int i = 0; i < height; i++)
    {
        getline(inputFile, line);
        string delimiter = " ";
        string value;
        for (int j = 0; j < width; j++)
        {
            value = line.substr(0, line.find(delimiter));
            expectedMatrix[i][j] = stoi(value);
            line.erase(0, line.find(delimiter) + delimiter.length());
        }
    }
    inputFile.close();

    string outDirectory = (argc == 3) ? argv[2] : "";
    ofstream outputFile;
    outputFile.open(outDirectory + "expected_output.txt");
    outputFile << stepsLimit << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outputFile << expectedMatrix[i][j] << ' ';
        }
        outputFile << endl;
    }
    outputFile.close();
    outputFile.open(outDirectory + "test_input.txt");
    outputFile << processesNumber << ' ' << stepsLimit << ' ' << height;
    outputFile.close();
    outputFile.open(outDirectory + "inMatrix.txt");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outputFile << inputMatrix[i][j] << ' ';
        }
        outputFile << endl;
    }
    outputFile.close();
    return 0;
}
