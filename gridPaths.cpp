#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <sstream>
using namespace std;

int solve_grid_paths_top_down(int n, vector<vector<char>> &grid) {
    constexpr int M = 1e9 + 7;
    vector<vector<int>> memo(n, vector<int>(n,-1)); // We init with a negative value because it is not a valid possibility for the problem

    function<int(int,int)> solve = [&](int i, int j) {
        if (i == n-1 && j == n-1 && grid[i][j] == '.') return 1; // OK we found a path
        if (i >= n || j >= n) return 0;
        int &res = memo[i][j]; // Reference to the value in table
        if (res != -1) return res; // If we have already seen this value
        res = 0;
        if(grid[i][j] == '.') {
            res += solve(i+1, j) + solve(i, j+1);
        }
        if (res >= M) res -= M; // To do the modulo (more efficient than using '%')
        return res;
    };

    return solve(0,0);
}

int main() {
    int n;
    cin >> n;
    vector<vector<char>> grid(n, vector<char>(n,'.'));
    for(int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for(int j = 0; j < n; j++) {
            if(row[j] == '*') {
                grid[i][j] = '*';
            }
        }
    }

    cout << solve_grid_paths_top_down(n, grid) << endl;
    return 0;
}