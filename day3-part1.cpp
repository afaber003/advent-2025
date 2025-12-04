#include <string>
#include <fstream>
#include <vector>

using namespace std;

inline bool customNoneOf(const vector<char>& noneOfThese, char itemToFind) {
    for (char item : noneOfThese) {
        if (itemToFind == item) {
            return false;
        }
    }
    return true;
}

inline uint indexOfBiggestBattery(const string& batteryGroup, const vector<char>& ignoreThese = {}) {
    int largestNumber = atoi((string() + batteryGroup[0]).c_str());
    uint currentIndex = 1, largestIndex = 0;
    for (; currentIndex < batteryGroup.length(); currentIndex++) {
        char value = batteryGroup[currentIndex];
        if (largestNumber < atoi((string() + value).c_str()) && customNoneOf(ignoreThese, value)) {
            largestNumber = atoi((string() + value).c_str());
            largestIndex = currentIndex;
        }
    }

    return largestIndex;
}

int processBatteryGroup(const string& batGroup) {
    uint largestNumberIndex = indexOfBiggestBattery(batGroup);
    if (largestNumberIndex < batGroup.length() - 1) { // easy case
        string substring = batGroup.substr(largestNumberIndex + 1);
        return atoi((string() + batGroup[largestNumberIndex] + substring[indexOfBiggestBattery(substring)]).c_str());
    } else {
        vector<char> ignoreThisOne = { batGroup[largestNumberIndex] };
        uint secondLargestIndex = indexOfBiggestBattery(batGroup, ignoreThisOne);
        return atoi((string() + batGroup[secondLargestIndex] + batGroup[largestNumberIndex]).c_str());
    }
}

int main() {
    ifstream inputFile("/home/afaber003/Desktop/codeStuff/c++/advent-2025/input-3-1.txt");
    long runningTotal = 0;
    string batteryGroup;
    while (getline(inputFile, batteryGroup)) {
        runningTotal += processBatteryGroup(batteryGroup);
    }
    printf("%ld\n", runningTotal);
}
