#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int minDistance(int a, int b, int c) {
    int minimum = a;
    if (b < minimum)
        minimum = b;
    if (c < minimum)
        minimum = c;
    return minimum;
}

int calculateDistance(const string& str1, const string& str2) {
    int len1 = str1.length() + 1;
    int len2 = str2.length() + 1;
    vector<vector<int> > distanceMatrix(len1, vector<int>(len2, 0));

    for (int i = 1; i < len1; i++)
        distanceMatrix[i][0] = i;

    for (int j = 1; j < len2; j++)
        distanceMatrix[0][j] = j;

    for (int col = 1; col < len2; col++) {
        for (int row = 1; row < len1; row++) {
            int cost = (str1[row - 1] == str2[col - 1]) ? 0 : 1;
            distanceMatrix[row][col] = minDistance(distanceMatrix[row - 1][col] + 1,      // deletion
                                 distanceMatrix[row][col - 1] + 1,      // insertion
                                 distanceMatrix[row - 1][col - 1] + cost); // substitution
        }
    }

    return distanceMatrix[len1 - 1][len2 - 1];
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<string> lines;
    string currentLine;
    while (getline(inputFile, currentLine)) {
        lines.push_back(currentLine);
    }
    inputFile.close();

    int numPairs = lines.size() / 2;  
    for (int i = 0; i < numPairs; i++) {
        string str1 = lines[i * 2];
        string str2 = lines[i * 2 + 1];
        str1.erase(remove(str1.begin(), str1.end(), '\n'), str1.end()); 
        str2.erase(remove(str2.begin(), str2.end(), '\n'), str2.end());

        int distance = calculateDistance(str1, str2);
        cout << "Levenshtein distance between '" << str1 << "' and '" << str2 << "' is: " << distance << endl;
    }

    return 0;
}
