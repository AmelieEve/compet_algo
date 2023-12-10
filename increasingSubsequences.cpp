//
// Created on 29/11/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Complexity: O(n*log(n))
void solve_increasing_subsequences_2(vector<int> &array) {
    int n = array.size();
    vector<int> lis; // 'lis[i]' represents the smallest value ending all length-(i+1) strictly increasing subsequence
    vector<int> idx; // At position 'i' in 'lis', what is the corresponding index in the array ?
    vector<int> prev(n, -1); // 'prev[i]' is the previous index in 'array' for the value at index 'i' in 'array',
                                    // for a strictly increasing subsequence ending at 'i'

    for(int i = 0; i < n; i++) {
        int v = array[i];
        int pos = lower_bound(begin(lis), end(lis), v) - begin(lis); // Binary search the position of 'v'
        if (pos == lis.size()) { // We found a new best subsequence
            lis.push_back(v);
            idx.push_back(i);
        } else { // Smaller value for a subsequence of length 'pos + 1'
            lis[pos] = v;
            idx[pos] = i;
        }
        if (pos != 0) {
            prev[i] = idx[pos - 1];
        }
    }

    cout << lis.size() << endl;
}

// Complexity: O(n^2)
void solve_increasing_subsequences(vector<int> &array) {
    int n = array.size();
    vector<int> lis(n,1);
    int best = 1;
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            if(array[j] < array[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
        best = max(best, lis[i]);
    }
    cout << best << endl;
}

int main() {
    int n;
    cin >> n;
    vector<int> array;
    for(int i = 0; i < n; i++) {
        int element;
        cin >> element;
        array.push_back(element);
    }

    solve_increasing_subsequences_2(array);
    return 0;
}