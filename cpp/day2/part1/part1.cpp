#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

bool CheckLine(vector<unsigned int> &linearray);
bool areAllIncreasing(vector<unsigned int> &linearray);
bool areAllDecreasing(vector<unsigned int> &linearray);
bool hasSmallDiff(vector<unsigned int> &linearray, bool isIncreasing);

int main(int argc, char *argv[])
{
    // VARIABLES
    string LineStr;
    unsigned int safeCount = 0;

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
        return -1; // Exit if file cannot be opened
    }

    // READ EVERY LINE
    while (getline(InputFile, LineStr)) // Until the file's last line...
    {
        vector<unsigned int> LineArray; // Dynamic storage for numbers
        stringstream ss(LineStr);
        unsigned int num;

        // Read all numbers dynamically
        while (ss >> num)
        {
            LineArray.push_back(num);
        }

        // Check if this line is safe
        if (CheckLine(LineArray))
        {
            safeCount++;
        }
        cout << "---------------------" << endl;
    }

    cout << "Total safe sequences: " << safeCount << endl;

    InputFile.close();

    return 0;
}

bool areAllIncreasing(vector<unsigned int> &linearray)
{
    // For every number in the array except the last one
    for (unsigned int i = 0; i < linearray.size() - 1; i++)
    {
        cout << "Now checking " << linearray[i] << " and " << linearray[i + 1] << endl;

        if (linearray[i] > linearray[i + 1])
        {
            return false; // Found a decrease, so not all numbers in the sequence are increasing.
        }
    }

    cout << "All numbers are increasing." << endl;
    return true;
}

bool areAllDecreasing(vector<unsigned int> &linearray)
{
    // For every number in the array except the last one
    for (unsigned int i = 0; i < linearray.size() - 1; i++)
    {
        cout << "Now checking " << linearray[i] << " and " << linearray[i + 1] << endl;

        if (linearray[i] < linearray[i + 1])
        {
            return false; // Found an increase, so not all numbers in the sequence are decreasing.
        }
    }

    cout << "All numbers are decreasing." << endl;
    return true;
}

bool hasSmallDiff(vector<unsigned int> &linearray, bool isIncreasing)
{
    unsigned int diff = 0;

    for (unsigned int i = 0; i < linearray.size() - 1; i++)
    {
        cout << "Now checking " << linearray[i] << " and " << linearray[i + 1] << endl;

        if (isIncreasing)
        {
            diff = linearray[i + 1] - linearray[i];
        }
        else
        {
            diff = linearray[i] - linearray[i + 1];
        }

        cout << "Difference is " << diff << endl;

        if (diff < 1 || diff > 3)
        {
            cout << "Difference is NOT acceptable." << endl;
            return false;
        }
    }

    cout << "Difference is acceptable." << endl;
    return true;
}

bool CheckLine(vector<unsigned int> &linearray)
{
    // The 2 conditions that have to be met
    bool isIncreasing = false;
    bool isDecreasing = false;
    bool smallDiff = false;

    // Check if the numbers are increasing or decreasing
    if (linearray.size() >= 2)
    {
        if (linearray[0] < linearray[1])
        {
            isIncreasing = areAllIncreasing(linearray);
        }
        else
        {
            isDecreasing = areAllDecreasing(linearray);
        }

        smallDiff = hasSmallDiff(linearray, isIncreasing);
    }

    // Final decision
    if ((isIncreasing || isDecreasing) && smallDiff)
    {
        cout << "Sequence is safe." << endl;
        return true;
    }
    else
    {
        cout << "Sequence is unsafe." << endl;
        return false;
    }
}