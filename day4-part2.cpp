#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

template <typename T>
pair<T,T> operator+(const pair<T,T> & l,const pair<T,T> & r) {
    return {l.first+r.first,l.second+r.second};
}

class Grid {
    vector<vector<char>> grid = {};

    bool isValid(const int& x, const int& y) {
        return !(y >= grid.size() || x >= grid[0].size() || y < 0 || x < 0);
    }

    bool isPaper(const int& x, const int& y) {
        if (!isValid(x, y)) exit(1);
        return grid[y][x] == '@';
    }

    int numberOfFilledSpacesNear(const int& x, const int& y) {
        int count = 0;
        vector<pair<int, int>> surroundings = getValidSurroundings(x, y);
        for (auto item : surroundings) {
            if (isPaper(item.first, item.second)) {
                count += 1;
            }
        }
        return count;
    }

    vector<pair<int, int>> getValidSurroundings(const int& x, const int& y) {
        static pair<int, int> modifications[] = {
                { 0, 1 },
                { 0, -1 },
                { 1, 0 },
                { -1, 0},
                { 1, 1 },
                { 1, -1 },
                { -1, 1 },
                { -1, -1 }
        };
        vector<pair<int, int>> validSpaces = {};
        pair<int, int> startingSpace = { x, y };
        for (auto mod : modifications) {
            pair<int, int> newSquare = startingSpace + mod;
            if (isValid(newSquare.first, newSquare.second)) {
                validSpaces.push_back(newSquare);
            }
        }
        return validSpaces;
    }

public:
    void addGridRow(vector<char> newRow) {
        grid.push_back(newRow);
    }

    vector<pair<int, int>> mapOfFreeSpaces(int lessThanThis) {
        vector<pair<int, int>> papersThatCanBeAccessed = {};
        for (int y = 0; y < grid.size(); y++) {
            for (int x = 0; x < grid[y].size(); x++) {
                if (!isPaper(x, y)) continue;
                int numberOfFilledOnes = numberOfFilledSpacesNear(x, y);
                if (numberOfFilledOnes < lessThanThis) {
                    papersThatCanBeAccessed.emplace_back(x, y);
                }
            }
        }
        return papersThatCanBeAccessed;
    }

    long removeAllAvailable(int lessThanThis) {
        long totalRemoved = 0;

        while (true) {
            vector<pair<int, int>> accessMap = mapOfFreeSpaces(lessThanThis);
            if (accessMap.empty()) break;
            for (auto space : accessMap) {
                grid[space.second][space.first] = '.';
                totalRemoved += 1;
            }
        }

        return totalRemoved;
    }
};


int main() {
    ifstream inputFile("/home/afaber003/Desktop/codeStuff/c++/advent-2025/input-4-2.txt");
    string gridLine;
    Grid grid = Grid();
    while (getline(inputFile, gridLine)) {
        vector<char> newLine = {};
        for (char character : gridLine) {
            newLine.push_back(character);
        }
        grid.addGridRow(newLine);
    }
    printf("%ld\n", grid.removeAllAvailable(4));
}
