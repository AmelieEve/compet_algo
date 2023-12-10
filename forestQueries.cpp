//
// Created on 17/11/23.
//

#include <iostream>
#include <vector>
using namespace std;

void solve_forest_queries(vector<vector<char>> &forest, vector<vector<int>> &queries) {
    int n = forest.size();
    vector<vector<int>> sum(n+1, vector<int>(n+1, 0));
    for (int y = 1; y <= n; y++) {
        for(int x = 1; x <= n; x++) {
            sum[y][x] = sum[y][x-1] + sum[y-1][x] - sum[y-1][x-1] + (forest[y-1][x-1] == '*');
        }
    }
    for (vector<int> query : queries) {
        int y1 = query[0];
        int x1 = query[1];
        int y2 = query[2];
        int x2 = query[3];
        cout << (sum[y2][x2] - sum[y2][x1-1] - sum[y1-1][x2] + sum[y1-1][x1-1]) << endl;
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<char>> forest(n, vector<char>(n,'.'));
    for(int y = 0; y < n; y++) {
        string row;
        cin >> row;
        for(int x = 0; x < n; x++) {
            if(row[x] == '*') {
                forest[y][x] = '*';
            }
        }
    }

    vector<vector<int>> queries;
    for(int i = 0; i < q; i++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        queries.push_back({y1,x1,y2,x2});
    }

    solve_forest_queries(forest, queries);

    return 0;
}