#include <string>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;


long getSafeCount(const vector<pair<long long, long long>>& includedRanges, const vector<long long>& onesToCheck) {
    long total = 0;
    for (auto oneToCheck : onesToCheck) {
        for (auto item : includedRanges) {
            if (oneToCheck <= item.second && oneToCheck >= item.first) {
                total += 1;
                break;
            }
        }
    }

    return total;
}


int main() {
    ifstream inputFile("/home/afaber003/Desktop/codeStuff/c++/advent-2025/input-5-1.txt");
    string inputLine;
    vector<pair<long long, long long>> goodRanges = {};
    vector<long long> badOnes = {};
    bool isSearchingGood = true;
    while (getline(inputFile, inputLine)) {
        if (inputLine.empty()) { isSearchingGood = false; continue; }
        if (isSearchingGood) {
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
        } else {
            badOnes.emplace_back(atoll(inputLine.c_str()));
        }
    }
    printf("%ld\n", getSafeCount(goodRanges, badOnes));
}
