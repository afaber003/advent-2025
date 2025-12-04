#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

inline int toNum(const char& c) {
    return atoi((string() + c).c_str());
}

int getSmallestIndex(const string& input) {
    int smallestNumber = 10;
    int indexToReturn = -1;
    for (int i = 0; i < input.length(); i++) {
        if (smallestNumber > toNum(input[i])) {
            smallestNumber = toNum(input[i]);
            indexToReturn = i;
        }
    }
    return indexToReturn;
}

int getLargestIndex(const string& input, int overrideLength = -1) {
    int smallestNumber = -1;
    int indexToReturn = -1;
    for (int i = 0; i < (overrideLength == -1 ? input.length() : (input.length() - overrideLength + 1)); i++) {
        if (smallestNumber < toNum(input[i])) {
            smallestNumber = toNum(input[i]);
            indexToReturn = i;
        }
    }
    return indexToReturn;
}

string processBatteryGroup(const string& batteryGroup, const int& numberToSelect) {
    if (numberToSelect == 0) return {};
    string finalAnswer = batteryGroup;

    int indexToStopAt = getLargestIndex(batteryGroup, numberToSelect);
    int copy = indexToStopAt;
    for (int i = 0; i < copy; i++) {
        int indexToRemove = getSmallestIndex(finalAnswer.substr(0, indexToStopAt));
        finalAnswer = finalAnswer.substr(0, indexToRemove) + finalAnswer.substr(indexToRemove + 1);
        indexToStopAt--;
        if (finalAnswer.length() == numberToSelect) break;
    }

    finalAnswer = finalAnswer.substr(0, indexToStopAt);
    string substring = processBatteryGroup(batteryGroup.substr(copy+1), numberToSelect - (finalAnswer.length() + 1));
    return finalAnswer + batteryGroup[copy] + substring;
}

int main() {
    ifstream inputFile("/home/afaber003/Desktop/codeStuff/c++/advent-2025/input-3-2.txt");
    long long runningTotal = 0;
    string batteryGroup;
    while (getline(inputFile, batteryGroup)) {
        runningTotal += atoll(processBatteryGroup(batteryGroup, 12).c_str());
    }
    printf("%lld\n", runningTotal);
}
