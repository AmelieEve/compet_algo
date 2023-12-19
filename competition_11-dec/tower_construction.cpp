//
// Created on 11/12/23.
//

#include <iostream>
#include <vector>
using namespace std;

void solve_tower_construction(vector<int> &widths) {
    int count_towers = 1;
    for(int i = 1; i < widths.size(); i++) {
        if(widths[i] > widths[i-1]) {
            count_towers++;
        }
    }
    cout << count_towers << endl;
}

int main() {
    int n;
    cin >> n;
    vector<int> widths;
    for(int i = 0; i < n; i++) {
        int w;
        cin >> w;
        widths.push_back(w);
    }

    solve_tower_construction(widths);

    return 0;
}