//
// Created on 11/12/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve_increasing_subsequences(vector<int> &array) {
    int n = array.size();
    vector<int> lis;
    vector<int> idx;
    vector<int> prev(n, -1);

    for(int i = 0; i < n; i++) {
        int v = array[i];
        int pos = lower_bound(begin(lis), end(lis), v) - begin(lis);
        if (pos == lis.size()) {
            lis.push_back(v);
            idx.push_back(i);
        } else {
            lis[pos] = v;
            idx[pos] = i;
        }
        if (pos != 0) {
            prev[i] = idx[pos - 1];
        }
    }

    int res = lis.size();
    cout << res << " ";
    for(int i = 0; i < res; i++) {
        cout << lis[i];
        if(i < res - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;

    while(n != 0) {
        vector<int> array;
        for(int i = 0; i < n; i++) {
            int element;
            cin >> element;
            array.push_back(element);
        }
        solve_increasing_subsequences(array);
        cin >> n;
    }
    return 0;
}