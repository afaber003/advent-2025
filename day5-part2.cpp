#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;


unsigned long getSafeCount(vector<pair<long long, long long>>& includedRanges) {
    vector<pair<long long, long long>> boundariesList = {};
    int count = 0;
    for (auto nextRange : includedRanges) {
        bool addAnyWay = true;
        for (auto& existingRange : boundariesList) {

            // case where it eats the whole other range
            if (nextRange.first < existingRange.first && nextRange.second > existingRange.second) {
                existingRange.first = nextRange.first;
                existingRange.second = nextRange.second;
                addAnyWay = false;
            } // case where it is entirely within a range
            else if (nextRange.first >= existingRange.first && nextRange.second <= existingRange.second) {
                addAnyWay = false;
            } //  case where the new range is overlapping the front of the existing range
            else if (nextRange.first < existingRange.first && nextRange.second >= existingRange.first && nextRange.second <= existingRange.second) {
                existingRange.first = nextRange.first;
                addAnyWay = false;
            } // case for overlapping the end edge
            else if (nextRange.second > existingRange.second && nextRange.first > existingRange.first && nextRange.first < existingRange.second) {
                existingRange.second = nextRange.second;
                addAnyWay = false;
            }
        }
        if (addAnyWay) {
            boundariesList.emplace_back(nextRange);
        }
    }

    bool wasThereAChange = true;
    vector<pair<long long, long long>> nextBoundaryList = boundariesList;
    while (wasThereAChange) {
        nextBoundaryList.clear();
        wasThereAChange = false;
        for (auto& rangeToCheck : boundariesList) {
            for (auto existingRange : boundariesList) {
                // case where it eats the whole other range
                if (rangeToCheck.first < existingRange.first && rangeToCheck.second > existingRange.second) {
                    existingRange.first = rangeToCheck.first;
                    existingRange.second = rangeToCheck.second;
                    addAnyWay = false;
                } // case where it is entirely within a range
                else if (rangeToCheck.first >= existingRange.first && rangeToCheck.second <= existingRange.second) {
                    boundariesList.rem
                } //  case where the new range is overlapping the front of the existing range
                else if (rangeToCheck.first < existingRange.first && rangeToCheck.second >= existingRange.first && rangeToCheck.second <= existingRange.second) {
                    existingRange.first = rangeToCheck.first;
                    addAnyWay = false;
                } // case for overlapping the end edge
                else if (rangeToCheck.second > existingRange.second && rangeToCheck.first > existingRange.first && rangeToCheck.first < existingRange.second) {
                    existingRange.second = rangeToCheck.second;
                    addAnyWay = false;
                }
            }
        }
    }

    return count;
}


int main() {
    ifstream inputFile("/home/afaber003/Desktop/codeStuff/c++/advent-2025/input-5-2.txt");
    string inputLine;
    vector<pair<long long, long long>> goodRanges = {};
    while (getline(inputFile, inputLine)) {
        if (inputLine.empty()) { break; }
        string firstOne = string();
        string secondOne = string();
        bool useSecondString = false;
        for (char item : inputLine) {
            if (item != '-') {
                if (useSecondString) {
                    secondOne += item;
                } else {
                    firstOne += item;
                }
            } else {
                useSecondString = true;
                continue;
            }
        }
        goodRanges.emplace_back(atoll(firstOne.c_str()), atoll(secondOne.c_str()));
    }
    printf("%lu\n", getSafeCount(goodRanges));
}
