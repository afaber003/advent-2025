#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct NumberSelected {
    int value;
    vector<int> indicesAvailable = {};
};

inline int toNum(const char& c) {
    return atoi((string() + c).c_str());
}

template<typename T>
inline bool noneOf(const vector<T>& items, const T& item) {
    for (T value : items) {
        if (item == value) {
            return false;
        }
    }
    return true;
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
    for (int i = 0; i < (overrideLength == -1 ? input.length() : (input.length() - overrideLength)); i++) {
        if (smallestNumber < toNum(input[i])) {
            smallestNumber = toNum(input[i]);
            indexToReturn = i;
        }
    }
    return indexToReturn;
}

string processBatteryGroup(const string& batteryGroup, const int& numberToSelect) {
    string finalAnswer = batteryGroup;

    int indexToStopAt = getLargestIndex(batteryGroup, numberToSelect);
    int copy = indexToStopAt;
    for (int i = 0; i < copy; i++) {
        int indexToRemove = getSmallestIndex(finalAnswer.substr(0, indexToStopAt));
        finalAnswer = finalAnswer.substr(0, indexToRemove) + finalAnswer.substr(indexToRemove + 1);
        indexToStopAt--;
        if (finalAnswer.length() == numberToSelect) break;
    }

    int numberToRemove = finalAnswer.length() - numberToSelect;
    string substring = batteryGroup.substr(copy+1);
    // printf("%s\n", substring.c_str());
    reverse(substring.begin(), substring.end());
    for (int i = 0; i < numberToRemove; i++) {
        int smallestIndex = getSmallestIndex(substring);
        substring = substring.substr(0, smallestIndex) + substring.substr(smallestIndex + 1);
    }
    finalAnswer = finalAnswer.substr(0, indexToStopAt);
    reverse(substring.begin(), substring.end());
    // printf("%s %c %s\n", finalAnswer.c_str(), batteryGroup[copy], substring.c_str());

    return finalAnswer + batteryGroup[copy] + substring;
}

int main() {
    ifstream inputFile("/Users/afaber003/Desktop/code stuff/c++/advent-2025/input-3-2.txt");
    long long runningTotal = 0;
    string batteryGroup;
    while (getline(inputFile, batteryGroup)) {
        runningTotal += atoll(processBatteryGroup(batteryGroup, 12).c_str());
    }
    printf("%lld\n", runningTotal);
}
