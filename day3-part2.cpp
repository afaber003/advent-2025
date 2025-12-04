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

string processBatteryGroup(const string& batteryGroup, const int& numberToSelect) {
    string finalAnswer = {};

    vector<int> largestNumbers = {};
    for (int i = 0; i < numberToSelect; i++) {
        int largestNumberSelected = -1;
        for (int index = 0; index < batteryGroup.length(); index++) {
            int value = toNum(batteryGroup[index]);
            if (value > largestNumberSelected && noneOf(largestNumbers, value)) {
                largestNumberSelected = value;
            }
        }
        largestNumbers.push_back(largestNumberSelected);
    }
    sort(largestNumbers.begin(), largestNumbers.end());
    reverse(largestNumbers.begin(), largestNumbers.end());

    vector<NumberSelected> numberInfos = {};
//    int amountAdded = 0;
    for (int numberSelected : largestNumbers) {
        numberInfos.emplace_back();
        numberInfos.back().value = numberSelected;
        for (int i = batteryGroup.length() - 1; i >= 0; i--) {
            if (toNum(batteryGroup[i]) == numberSelected) {
                numberInfos.back().indicesAvailable.insert(numberInfos.back().indicesAvailable.begin(), i);
//                amountAdded++;
//                if (amountAdded == numberToSelect) goto doneAddingNumbers;
            }
        }
    }

doneAddingNumbers:
    char* finalChars = (char*) calloc(batteryGroup.length(), sizeof(char));
    for (const auto& numberInfo : numberInfos) {
        for (auto index : numberInfo.indicesAvailable) {
            finalChars[index] = to_string(numberInfo.value)[0];
        }
    }
    for (int i = 0; i < batteryGroup.length(); i++) {
        if (finalChars[i] > 0) {
            finalAnswer += finalChars[i];
        }
    }
    free((void*) finalChars);
    return finalAnswer;
}

int main() {
    ifstream inputFile("/home/afaber003/Desktop/codeStuff/c++/advent-2025/input-3-2.txt");
    long runningTotal = 0;
    string batteryGroup;
    while (getline(inputFile, batteryGroup)) {
        runningTotal += atol(processBatteryGroup(batteryGroup, 4).c_str());
    }
    printf("%ld\n", runningTotal);
}
