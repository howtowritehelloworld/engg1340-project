#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printgametitle() {

    ifstream inputfile("gametitle.txt");

    string line;
    while (getline(inputfile, line)) {
        cout << line << endl;
    }

    inputfile.close();
}
