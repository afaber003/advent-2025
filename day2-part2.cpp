#include <string>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

bool isMadeOfWord(const string& word, const string& restOfWord) {
    if (word.length() > restOfWord.length()) return false;
    if (restOfWord.starts_with(word)) {
        if (word.length() < restOfWord.length()) {
            return isMadeOfWord(word, restOfWord.substr(word.length()));
        }
        return true;
    }
    return false;
}

static bool isValid(const string& id) {
    static map<string, bool> validMap;
    if (validMap.contains(id)) {
        return validMap.at(id);
    }
    for (int substrLength = 1; substrLength < id.length(); substrLength++) {
        string substring = id.substr(0, substrLength);
        if (isMadeOfWord(substring, id.substr(substrLength))) {
            validMap[id] = true;
            return true;
        }
    }
    validMap[id] = false;
    return false;
}

int main() {
    ifstream inputFile("/home/afaber003/Desktop/code stuff/c++/testing/input-2-2.txt");
    long runningTotal = 0;
    string begin, end, total;
    getline(inputFile, total);
    stringstream ss(total);
    while (getline(ss, begin, '-')) {
        if (getline(ss, end, ',')) {
            // nada
        } else {
            getline(ss, end);
        }
        long start = atol(begin.c_str());
        long stop = atol(end.c_str());
        for (; start <= stop; start++) {
            if (isValid(to_string(start))) {
                runningTotal += start;
            }
        }
    }
    printf("%ld\n", runningTotal);
}
