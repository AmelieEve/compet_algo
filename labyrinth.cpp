//
// Created on 19/12/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
using namespace std;

namespace labyrinth {
    using pii = pair<int, int>;
    pii operator-(const pii& p1, const pii& p2) {
        return {p1.first - p2.first, p1.second - p2.second};
    }
    pii operator+(const pii& p1, const pii& p2) {
        return {p1.first + p2.first, p1.second + p2.second};
    }
}

void solve_monsters(const vector<string>& grid) {
    using namespace labyrinth;
    const int N = grid.size();
    const int M = grid[0].size();
    const int INF = 1e9;

    // Possible moves
    map<pii, string> delta2string {{{-1, 0}, "U"}, {{1, 0}, "D"}, {{0, -1}, "L"}, {{0,1}, "R"}};
    vector<vector<int>> us(N, vector<int>(M, INF));
    queue<pii> q;
    pii exit;

    // First we spot our starting point and the exit
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'A') {
                us[i][j] = 0;
                q.emplace(i, j);
            }
            if (grid[i][j] == 'B') {
                exit = pii(i,j);
            }
        }
    }

    map<pii, pii> prev;

    auto bfs = [&](queue<pii>& q, vector<vector<int>>& m, map<pii, pii>& prev) {
        while (!q.empty()) {
            pii cur = q.front(); q.pop();
            for (auto delta : vector<pii>{{0,-1},{0,1},{-1,0},{1,0}}) {
                pii nxt = cur + delta;

                // If we are in the grid bounds, not running into a wall, and not going to an already visited case
                if (nxt.first >= 0 && nxt.first < N && nxt.second >= 0 && nxt.second <M &&
                    grid[nxt.first][nxt.second] != '#' && m[nxt.first][nxt.second] == INF) {
                    q.push(nxt);
                    m[nxt.first][nxt.second] = m[cur.first][cur.second] + 1;
                    prev[nxt] = cur; // We keep track here from where we came
                }
            }
        }
    };

    // Compute distances from the agent
    bfs(q, us, prev);

    if (us[exit.first][exit.second] != INF) {
        cout << "YES\n";
        stack<string> path;
        pii cur = exit;
        while (prev.count(cur)) {
            pii nxt = prev[cur];
            path.push(delta2string[cur - nxt]);
            cur = nxt;
        }
        cout << path.size() << '\n';
        while (!path.empty()) {
            cout << path.top();
            path.pop();
        }
        return;
    }
    cout << "NO\n";
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> grid;
    for(int i = 0; i < n; i++) {
        string line;
        cin >> line;
        grid.push_back(line);
    }

    solve_monsters(grid);

    return 0;
}