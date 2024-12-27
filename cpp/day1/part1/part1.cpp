#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

unsigned int FindMin(vector<unsigned int> &v);
unsigned int ComparePair(vector<unsigned int> &LeftVec, vector<unsigned int> &RightVec);
void PrintColumns(vector<unsigned int> &LeftCol, vector<unsigned int> &RightCol);
void PrintVector(vector<unsigned int> &Vec);
bool FindAndRemove(vector<unsigned int> &v, unsigned int value);

int main(int argc, char *argv[])
{
    // VARIABLES
    vector<unsigned int> LeftCol;
    vector<unsigned int> RightCol;
    string LineStr;
    int i, a, b, VecSize, TotalDistance = 0;

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

    // Start comparing pairs
    while (!LeftCol.empty() && !RightCol.empty()) 
    {
        TotalDistance += ComparePair(LeftCol, RightCol);
    }
    cout << endl << "Total distance is " << TotalDistance << endl; 

    return 0;
}

unsigned int FindMin(vector<unsigned int> &v)
{   
    // VARIABLES
    int vSize = v.size(); // Get the vector's size
    int current_min = v.front(); // Assume that the current min is the first element in the vector
    int i;

    // FIND THE MIN
    for (i = 0; i < vSize; i++)
    {
        if (v[i] < current_min)
        {
            current_min = v[i];
        }
    }

    return current_min;
}

unsigned int ComparePair(vector<unsigned int> &LeftVec, vector<unsigned int> &RightVec)
{
    cout << endl << "The Left vector is ";
    PrintVector(LeftVec);
    cout << "The Right vector is ";
    PrintVector(RightVec);

    // Find the mins of both columns
    unsigned int LeftMin = FindMin(LeftVec);
    unsigned int RightMin = FindMin(RightVec);
    int diff;

    cout << "Left min is\t" << LeftMin << endl;
    cout << "Right min is\t" << RightMin << endl;

    // Find how far apart they are
    diff = LeftMin - RightMin;

    // Always get the absolute value of the subtraction
    if ( diff < 0 ) // If the number is negative
    {
        diff = RightMin - LeftMin; // Save the other subtraction
    }

    cout << "Their difference is " << diff << endl;

    // Remove them from their corresponding vectors
    FindAndRemove(LeftVec, LeftMin);
    FindAndRemove(RightVec, RightMin);

    return diff;
}

void PrintColumns(vector<unsigned int> &LeftCol, vector<unsigned int> &RightCol)
{
    // GET THE SIZE OF THE COLUMNS
    int VecSize = LeftCol.size(); // The LeftCol has the same length with the RightCol, so we only need to use one of 'em.

    // PRINT ALL ELEMENTS
    cout << "LEFT\t" << "RIGHT" << endl;
    for (int i = 0; i < VecSize; i++)
    {
        cout << LeftCol[i] << "\t" << RightCol[i] << endl;
    }

    cout << "Min from the left: " << FindMin(LeftCol) << endl;
    cout << "Min from the right: " << FindMin(RightCol) << endl;

    return;
}

void PrintVector(vector<unsigned int> &Vec)
{
    // GET THE SIZE OF THE COLUMNS
    int VecSize = Vec.size();

    // PRINT ALL ELEMENTS
    cout << "\t[";
    for (int i = 0; i < VecSize; i++)
    {
        cout << Vec[i];

        //  Do not place a comma after the last number
        if (i != VecSize - 1)
        {
            cout << ",";
        }
        
    }
    cout << "]" << endl;

    return;
}

bool FindAndRemove(vector<unsigned int> &v, unsigned int value)
{   
    // Find the index of the first occurrence with thge given value
    auto itr = find(v.begin(), v.end(), value);

    if (itr != v.end()) // If it is not the end
    {
        v.erase(itr); // Erase it
        return true;
    }
    else
    {
        return false;
    }
}