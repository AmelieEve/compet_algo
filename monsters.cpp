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

namespace monsters {
    using pii = pair<int, int>;
    pii operator-(const pii& p1, const pii& p2) {
        return {p1.first - p2.first, p1.second - p2.second};
    }
    pii operator+(const pii& p1, const pii& p2) {
        return {p1.first + p2.first, p1.second + p2.second};
    }
}

void solve_monsters(const vector<string>& grid) {
// Idea: We use two bfs to compute the distances from the monsters and the distances from the agent.
// Then, if we find an exit that we can reach faster than any monster, it means that we are safe to
// take it. We need to keep track of the best previous cell from a given cell during bfs in order
// to be able to print the agent path from it starting position to the chosen exit point.
    using namespace monsters;
    const int N = grid.size();
    const int M = grid[0].size();
    const int INF = 1e9;

    // Possible moves
    map<pii, string> delta2string {{{-1, 0}, "U"}, {{1, 0}, "D"}, {{0, -1}, "L"}, {{0,1}, "R"}};
    // Monsters locations and our starting point
    vector<vector<int>> monsters(N, vector<int>(M, INF));
    vector<vector<int>> us(N, vector<int>(M, INF));
    // Queues for the two bfs
    queue<pii> q1, q2;
    // Exits location
    vector<pii> exits;

    // First we spot the monsters, our starting point, and the possible exits. We then initialize the queues for the two bfs.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'M') {
                monsters[i][j] = 0;
                q1.emplace(i, j);
            }
            if (grid[i][j] == 'A') {
                us[i][j] = 0;
                q2.emplace(i, j);
            }
            if (i == 0 || j == 0 || i == N - 1 || j == M - 1) {
                if (grid[i][j] != '#') {
                    exits.emplace_back(i, j);
                }
            }
        }
    }

    map<pii, pii> prev1, prev2;

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

    // Compute distances from the monsters
    bfs(q1, monsters, prev1);

    // Compute distances from the agent
    bfs(q2, us, prev2);

    // For each exit, we check if the distance from the agent is lesser than the distances from the monsters
    for (pii e : exits) {
        if (us[e.first][e.second] < monsters[e.first][e.second]) { // We can reach an exit faster than any monster
            cout << "YES\n";
            stack<string> path;
            pii cur = e;
            while (prev2.count(cur)) {
                pii nxt = prev2[cur];
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