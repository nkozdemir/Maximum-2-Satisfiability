#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

int count_satisfied(vector<pair<string, string>>& clauses, unordered_map<string, bool>& assignment) {
    int count = 0;
    for (auto c : clauses) {
        if (assignment[c.first] || assignment[c.second]) { 
            count++;
        }
    }
    return count;
}

int brute_force(vector<pair<string, string>>& clauses, vector<string>& variables) {
    int max_satisfied = 0;
    for (int i = 0; i < pow(2, variables.size()); i++) {
        unordered_map<string, bool> assignment;
        for (int j = 0; j < variables.size(); j++) {
            int val = i & (1 << j);
            if (val > 0)
                assignment[variables[j]] = 1;
            else
                assignment[variables[j]] = 0;
            assignment["!" + variables[j]] = !assignment[variables[j]];
        }
        int satisfied = count_satisfied(clauses, assignment);
        if (satisfied > max_satisfied)
            max_satisfied = satisfied;
    }
    for (int i = 0; i < pow(2, variables.size()); i++) {
        unordered_map<string, bool> assignment;
        for (int j = 0; j < variables.size(); j++) {
            int val = i & (1 << j);
            if (val > 0)
                assignment[variables[j]] = 1;
            else
                assignment[variables[j]] = 0;
            assignment["!" + variables[j]] = !assignment[variables[j]];
        }
        int satisfied = count_satisfied(clauses, assignment);
        if (satisfied == max_satisfied) {
            for (auto var : variables) {
                cout << var << "=" << assignment[var] << " ";
            }
            cout << endl;
        }
    }
    
    return max_satisfied;
}

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

void printClauses(vector<pair<string, string>> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << "{" << vec[i].first << ", " << vec[i].second << "}";
    }
    cout << endl;
}

void printVariables(vector<string> vec) {
    for (auto p : vec) {
        cout << p << " ";
    }
    cout << endl;
}

vector<string> generateVariables(vector<pair<string, string>> clauses) {
    int highestNumber = 0;
    
    for (const auto& var : clauses) {
        string var1 = var.first;
        string var2 = var.second;
        
        if (var1[0] == '!')
            var1 = var1.substr(1);
        if (var2[0] == '!')
            var2 = var2.substr(1);
        
        string num1 = var1.substr(1);
        string num2 = var2.substr(1);
        
        if (all_of(num1.begin(), num1.end(), ::isdigit)) {
            int currentNum = stoi(num1);
            if (currentNum > highestNumber)
                highestNumber = currentNum;
        }
        if (all_of(num2.begin(), num2.end(), ::isdigit)) {
            int currentNum = stoi(num2);
            if (currentNum > highestNumber)
                highestNumber = currentNum;
        }
    }
    
    vector<string> variablesUpToHighest;
    for (int i = 1; i <= highestNumber; ++i) {
        string variable = "x" + to_string(i);
        variablesUpToHighest.push_back(variable);
    }
    
    return variablesUpToHighest;
}

// A main function to test specified amount of random samples
/*
int main() {
    int numSamples = 15; // sample size
    srand((unsigned)time(NULL));
    
    for (int i = 0; i < numSamples; i++) {
        cout << "----- Iteration " << i+1 << " -----" << endl;
        
        int numVar = rand() % 5 + 2;
        cout << "Number of variables: " << numVar << endl;
        int x = numVar % 2 == 0 ? numVar / 2 : numVar / 2 + 1;
        int numClause = rand() % 8 + x;
        cout << "Number of clauses: " << numClause << endl;
        
        vector<pair<string, string>> clauses;
        vector<string> variables;
        generateSample(clauses, variables, numVar, numClause);
        cout << "Variables: ";
        printVariables(variables);
        cout << "Clauses: ";
        printClauses(clauses);
        cout << "Truth assignment(s) satisfying maximum number of clauses: " << endl;
        int max_satisfied = brute_force(clauses, variables);
        cout << "Maximum number of clauses satisfied: " << max_satisfied << endl;
    }
    
    return 0;
}
*/

// A main function to test multiple clauses manually
/*
int main() {
    srand((unsigned)time(NULL));
    
    vector<vector<pair<string, string>>> clauses = {
        {{"!x6", "!x1"}, {"x6", "!x1"}, {"!x4", "x5"}, {"!x6", "x1"}, {"x2", "!x3"}, {"!x5", "!x2"}, {"!x5", "x6"}, {"x4", "x5"}},
        {{"x2", "x7"}, {"!x6", "x7"}, {"x6", "x1"}, {"x1", "!x5"}, {"!x7", "!x1"}, {"!x6", "!x7"}, {"!x4", "x5"}, {"x6", "x4"}},
        {{"!x4", "x7"}, {"x6", "!x8"}, {"x8", "x9"}, {"x2", "!x4"}, {"x3", "!x5"}, {"!x2", "x4"}, {"x4", "!x1"}, {"x8", "!x9"}},
        {{"x4", "x3"}, {"!x10", "x3"}, {"!x12", "x7"}, {"!x12", "!x3"}, {"!x11", "x2"}, {"!x8", "!x2"}, {"x8", "!x1"}, {"x2", "!x7"}},
        {{"!x10", "x13"}, {"!x6", "x11"}, {"x10", "!x14"}, {"x9", "!x14"}, {"x9", "!x1"}, {"!x15", "x2"}, {"x4", "!x5"}, {"!x13", "x1"}}
    };
    
    for (int i = 0; i < clauses.size(); i++) {
        vector<string> variables = generateVariables(clauses[i]);
        cout << "----------" << endl;
        cout << "Clauses: ";
        printClauses(clauses[i]);
        cout << "Variables: ";
        printVariables(variables);
        cout << "Truth assignment(s) satisfying maximum number of clauses: " << endl;
        int max_satisfied = brute_force(clauses[i], variables);
        cout << "Maximum number of clauses satisfied: " << max_satisfied << endl;
    }
    
    return 0;
}
 */

// A main function to measure the running time of the brute force algorithm
/*
int main() {
    srand((unsigned)time(NULL));
    
    vector<pair<string, string>> clauses = {{"x3", "x2"}, {"x1", "!x4"}, {"x6", "x5"}, {"x5", "x1"}, {"x2", "!x3"}, {"x4", "!x2"}, {"!x6", "x2"}, {"x3", "!x6"}, {"!x3", "x4"}, {"x6", "!x5"}};
    
    auto start = std::chrono::high_resolution_clock::now();
    
    vector<string> variables = generateVariables(clauses);
    cout << "----------" << endl;
    cout << "Clauses: ";
    printClauses(clauses);
    cout << "Variables: ";
    printVariables(variables);
    cout << "Truth assignment(s) satisfying maximum number of clauses: " << endl;
    int max_satisfied = brute_force(clauses, variables);
    cout << "Maximum number of clauses satisfied: " << max_satisfied << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
    
    return 0;
}
 */
