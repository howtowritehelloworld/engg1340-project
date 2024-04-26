#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printgametitle(string name) {

    ifstream inputfile(name + ".txt");

    string line;
    while (getline(inputfile, line)) {
        cout << line << endl;
    }

    inputfile.close();
}