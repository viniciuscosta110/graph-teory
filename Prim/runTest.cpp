// If bash is not available, run the prim tests with this file

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include<unistd.h>
#include <fstream>

#include "handleArgs.h"

using namespace std;

int main() {
  // The tests are at ./instances
  string instancesPath = "instances/";

  // The solutions are at ./gabarito_agm.txt
  string solutionsFilePath = "./gabarito_agm.txt";

  vector<string> tests;
  vector<string> solutions;
  
  // Read the tests paths
  for (const auto & entry : filesystem::directory_iterator(instancesPath)) {
    tests.push_back(entry.path());
  }

  // Read the solutions 
  ifstream solutionsFile(solutionsFilePath);
  string line;
  while (getline(solutionsFile, line)) {
    solutions.push_back(line);
  }

  // Run the tests
  for (string test : tests) {
    cout << "Running test " << test << endl;
    string command = "./prim -f " + test + " -s";
    
    // Run the command and get the output
    FILE *fp = popen(command.c_str(), "r");
    char buffer[1024];
    string output = "";
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
      output += buffer;
    }

    pclose(fp);
    
    // Compare the output with the solution
    for (string solution : solutions) {
      string solutionTestName = solution.substr(0, solution.find(" "));
      string solutionTest = solution.substr(solution.find(" ")+1);
      output = to_string(stoi(output));

      if(test == solutionTestName) {
        if (output != solutionTest) { 
          cout << "Expected: " << solutionTest << "\nGot: " << output << "\n";
          cout << "\e[32mOK\e[0m" << endl;
        } else {
          cout << "Test " << test << " \e[31mfailed!\e[0m" << endl;
          cout << "Expected: " << solutionTest << endl;
          cout << "Got: " << output << endl;
        }
      }    
    }

    cout << endl;
  }
  
}