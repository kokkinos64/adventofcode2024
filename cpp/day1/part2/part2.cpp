#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
unsigned int FindSimScore(unsigned int num, vector<unsigned int> &RightVec);

int main(int argc, char *argv[])
{
    // VARIABLES
    vector<unsigned int> LeftCol;
    vector<unsigned int> RightCol;
    string LineStr;
    int i, a, b, TotalSimilarityScore = 0;

    // CHECK CMD ARGUMENTS
    if (argc < 2)
    {
        cerr << "Invalid arguments." << endl;
        cout << "Usage: ./run <filename.txt>" << endl;

        return -1;
    }

    // OPEN THE FILE
    ifstream InputFile(argv[1]);

    // CHECK IF OPENING WAS UNSUCCESSFUL
    if (!InputFile.is_open())
    {
        cerr << "Failed to open the file." << endl;
    }

    // READ THE TWO COLUMNS
    while (getline(InputFile, LineStr)) // Until the file's last line...
    {
        sscanf(LineStr.c_str(), "%d   %d\n", &a, &b); // Read the line
        LeftCol.push_back(a);                         // Save the left number
        RightCol.push_back(b);                        // Save the right number
        i++;                                          // Go to the next line
    }
    cout << "Just finished reading the file." << endl;

    // PrintColumns(LeftCol, RightCol);

    // Start calculating Similarity scores for every number in the left column
    for (auto element : LeftCol)
    {
        TotalSimilarityScore += FindSimScore(element, RightCol);
    }

    cout << "The total similarity score is " << TotalSimilarityScore << endl;    

    return 0;
}

// For a given number of the left column, find out how many times it appears on the right column, and return its similarity score
unsigned int FindSimScore(unsigned int num, vector<unsigned int> &RightVec)
{
    // Variables
    unsigned int DetectionCount = 0, SimScore = 0;

    for (auto element : RightVec)
    {
        if (element == num)
        {
            DetectionCount++;
        }
    }

    cout << "Number " << num << " appeared " << DetectionCount << " times in the right column." << endl;

    SimScore = num * DetectionCount;

    cout << "Its Similarity Score is " << SimScore << endl;

    return SimScore;
}