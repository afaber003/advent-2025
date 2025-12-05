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

    int numberOfFreePapers(int lessThanThis) {
        int total = 0;
        for (int x = 0; x < grid[0].size(); x++) {
            for (int y = 0; y < grid.size(); y++) {
                if (!isPaper(x, y)) continue;
                int numberOfFilledOnes = numberOfFilledSpacesNear(x, y);
                if (numberOfFilledOnes < lessThanThis) {
                    total += 1;
                }
            }
        }
        return total;
    }
};


int main() {
    ifstream inputFile("/home/afaber003/Desktop/codeStuff/c++/advent-2025/input-4-1.txt");
    string gridLine;
    Grid grid = Grid();
    while (getline(inputFile, gridLine)) {
        vector<char> newLine = {};
        for (char character : gridLine) {
            newLine.push_back(character);
        }
        grid.addGridRow(newLine);
    }
    printf("%d\n", grid.numberOfFreePapers(4));
}
