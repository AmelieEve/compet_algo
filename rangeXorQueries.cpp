//
// Created on 17/11/23.
//
#include <iostream>
#include <vector>
using namespace std;

int solve_range_xor_queries(vector<int> &arrayValues, int a, int b) {
    if(a == b) {
        return arrayValues[a-1];
    }

    int res = arrayValues[a-1];
    for(int i = a; i <= b-1; i++) {
        res = res^arrayValues[i];
    }

    return res;
}

void solve_range_xor_queries2(const vector<int>& values, const vector<pair<int, int>>&requests) {
    int n = values.size();
    vector<int> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] ^ values[i - 1];
    }
    for (auto [a, b] : requests) {
        cout << (sum[b] ^ sum[a - 1]) << endl;
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> arrayValues;
    for(int i = 0; i < n; i++) {
        int val;
        cin >> val;
        arrayValues.push_back(val);
    }

    vector<pair<int,int>> queries;
    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        queries.emplace_back(a,b);
    }
    solve_range_xor_queries2(arrayValues,queries);

    return 0;
}