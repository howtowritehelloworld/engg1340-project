#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void printgametitle(string name) {

    ifstream inputfile(name + ".txt");
    vector lines;
    
    string line;
    while (getline(inputfile, line)) {
        lines.push_back(line);
    }

    inputfile.close();
}
