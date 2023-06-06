#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

void generateSample(vector<pair<string,string>> & clauses, vector<string> & vars, int numVars, int numClauses) {
    for (int i = 1; i <= numVars; i++) {
        string var = "x" + to_string(i);
        vars.push_back(var);
    }

    for (int i = 0; i < numClauses; i++) {
        string var1, var2;
        bool negate1, negate2;

        int index1 = rand() % numVars;
        int index2 = rand() % numVars;
        while (index1 == index2) {
            index2 = rand() % numVars;
        }
        var1 = vars[index1];
        var2 = vars[index2];

        negate1 = rand() % 2 == 0;
        negate2 = rand() % 2 == 0;
        if (negate1)
            var1 = "!" + var1;
        if (negate2)
            var2 = "!" + var2;

        clauses.push_back(make_pair(var1, var2));
    }
}

void outputSample(int numVars, int numClauses, const vector<pair<string, string>> & vec, bool append) {
    string filename = "sample.txt";
    ofstream outputFile;
    
    if (append)
        outputFile.open(filename, fstream::app);
    else
        outputFile.open(filename);
        
    if (!outputFile) {
        cerr << "Error opening the file." << endl;
        return;
    }

    outputFile << "[";
    for (int i = 0; i < vec.size(); i++) {
        if (i == vec.size() - 1)
            outputFile << "(\"" << vec[i].first << "\", \"" << vec[i].second << "\")";
        else
            outputFile << "(\"" << vec[i].first << "\", \"" << vec[i].second << "\"), ";
    }
    outputFile << "]," << endl;

    outputFile.close();
}


int main() {
    srand((unsigned)time(NULL));
    
    int numVars, numClauses, choice;
    vector<pair<string, string>> clauses;
    vector<string> variables;
    
    cout << "1. Generate a sample" << endl;
    cout << "2. Generate many samples" << endl;
    cout << "Choose an option: ";
    cin >> choice;
    
    if (choice == 1) {
        cout << "Enter the number of variables to be created: ";
        cin >> numVars;
        while (numVars < 2) {
            cout << "Enter a valid number: ";
            cin >> numVars;
        }
        cout << "Enter the number of clauses to be generated: ";
        cin >> numClauses;
        while (numClauses < 0) {
            cout << "Enter a valid number: ";
            cin >> numClauses;
        }
        generateSample(clauses, variables, numVars, numClauses);
        outputSample(numVars, numClauses, clauses, false);
        cout << "Samples printed to sample.txt file successfully." << endl;
        clauses.clear();
        variables.clear();
    }
    else if (choice == 2) {
        int sampleSize;
        cout << "Enter the number of formulas to be generated: ";
        cin >> sampleSize;
        
        while (sampleSize < 0) {
            cout << "Enter a valid number: ";
            cin >> sampleSize;
        }
        
        numVars = rand() % 8 + 2;
        int x = numVars % 2 == 0 ? numVars / 2 : numVars / 2 + 1;
        numClauses = rand() % 10 + x;
        generateSample(clauses, variables, numVars, numClauses);
        outputSample(numVars, numClauses, clauses, false);
        clauses.clear();
        variables.clear();
        
        for (int i = 1; i <= sampleSize; i++) {
            numVars = rand() % 8 + 2;
            int x = numVars % 2 == 0 ? numVars / 2 : numVars / 2 + 1;
            numClauses = rand() % 10 + x;
            generateSample(clauses, variables, numVars, numClauses);
            outputSample(numVars, numClauses, clauses, true);
            clauses.clear();
            variables.clear();
        }
        
        cout << "Samples printed to sample.txt file successfully." << endl;
    }
    else {
        cout << "Invalid option" << endl;
        return 1;
    }

    return 0;
}
