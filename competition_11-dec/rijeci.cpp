//
// Created on 11/12/23.
//

#include <iostream>
using namespace std;

pair<int,int> solve_rijeci(int n) {
    if(n == 0) {
        return {1,0};
    } else if(n == 1) {
        return {0,1};
    } else {
        pair<int,int> previous = solve_rijeci(n-1);
        pair<int,int> prevPrevious = solve_rijeci(n-2);
        return {prevPrevious.first + previous.first, prevPrevious.second + previous.second};
    }
}

int main() {
    int n;
    cin >> n;

    pair<int,int> res = solve_rijeci(n);
    cout << res.first << " " << res.second << endl;

    return 0;
}

#if 0
pair<int,int> solve_rijeci(int n) {
    if(n == 0) {
        return {1,0};
    } else if(n == 1) {
        return {0,1};
    } else {
        pair<int,int> previous = solve_rijeci(n-1);
        pair<int,int> prevPrevious = solve_rijeci(n-2);
        return {prevPrevious.first + previous.first, prevPrevious.second + previous.second};
    }
}
#endif