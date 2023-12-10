//
// Created on 06/11/23.
//
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int solve_coin_combinations_I_top_down(int X, const vector<int>& coins) {
    constexpr int M = 1e9 + 7;
    vector<int> memo(X + 1, -1); // We init with a negative value because it is not a valid possibility for the problem

    function<int(int)> solve = [&](int sum) {
        if (sum == 0) return 1; // OK we found a valid coins combination
        if (sum < 0) return 0; // Because I don't check 'sum - coin >= 0' below
        int &res = memo[sum]; // Reference to the value in table
        if (res != -1) return res; // If we have already seen this value
        res = 0;
        for (int coin: coins) { // At each step, we consider all the coins, because the order matter
            res += solve(sum - coin); // For each value from 1 to X, the ways to sum up to this value are computed and stored in memo
            if (res >= M) res -= M; // To do the modulo (more efficient than using '%')
        }
        return res;
    };

    return solve(X);
}

int main() {
    int n;
    int x;
    cin >> n >> x;
    vector<int> c;
    for(int i = 0; i < n; i++) {
        int val;
        cin >> val;
        c.push_back(val);
    }

    int res = solve_coin_combinations_I_top_down(x,c);
    cout << res << endl;

    return 0;
}