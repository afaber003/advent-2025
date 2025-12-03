#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

struct {
    int value = 50;
    ushort zeros = 0;
    
    void addValue(int newVal) {
        int copy = newVal;
        bool isNegative = newVal < 0;
        while (copy != 0) {
            value += isNegative ? -1 : 1;
            if (value == -1) value = 99;
            if (value == 100) value = 0;
            zeros += value == 0 ? 1 : 0;
            copy += isNegative ? 1 : -1;
        }
    }

} currentState;

int main() {
    ifstream inputFile("input.txt");
    string nextLine;
    while (!inputFile.eof()) {
        getline(inputFile, nextLine);
        if (nextLine[0] == 'R') {
            currentState.addValue(atoi(nextLine.substr(1).c_str()));
        } else {
            currentState.addValue(-atoi(nextLine.substr(1).c_str()));
        }
        printf("%c, %d, %d\n", nextLine[0], atoi(nextLine.substr(1).c_str()), currentState.value);
    }
    printf("%d\n", (int) currentState.zeros);
    return 0;
}
