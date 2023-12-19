//
// Created on 19/12/23.
//

#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<char>> building;
vector<vector<bool>> visited;

// Check if the given position is within bounds and is a valid floor square
bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && building[x][y] == '.' && !visited[x][y];
}

// Perform DFS to explore the rooms
void explore(int x, int y) {
    visited[x][y] = true;
    // Possible moves: left, right, up, down
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (isValid(newX, newY)) {
            explore(newX, newY);
        }
    }
}

void solve_counting_rooms() {
    visited.assign(n, vector<bool>(m, false));
    int rooms = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (building[i][j] == '.' && !visited[i][j]) {
                explore(i, j);
                rooms++;
            }
        }
    }

    cout << rooms << endl;
}

int main() {
    cin >> n >> m;

    building.assign(n, vector<char>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> building[i][j];
        }
    }

    solve_counting_rooms();

    return 0;
}