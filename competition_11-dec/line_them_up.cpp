//
// Created on 11/12/23.
//

#include <iostream>
#include <vector>
using namespace std;

void solve_line_them_up(vector<string> &names) {
    int n = names.size();
    bool increasing = (names[0].compare(names[1]) < 0);
    for(int i = 2; i < n; i++) {
        bool newComp = (names[i-1].compare(names[i]) < 0);
        if (increasing != newComp) {
            cout << "NEITHER" << endl;
            return;
        }
    }
    if(increasing) cout << "INCREASING" << endl;
    else cout << "DECREASING" << endl;
}

int main() {
    int n;
    cin >> n;
    vector<string> names;
    for(int i = 0; i < n; i++) {
        string name;
        cin >> name;
        names.push_back(name);
    }

    solve_line_them_up(names);

    return 0;
}