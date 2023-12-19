//
// Created on 11/12/23.
//

#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

void solve_magic_trick(string &cards) {
    sort(cards.begin(), cards.end());
    auto last_unique_cards = unique(cards.begin(), cards.end());
    if(last_unique_cards != cards.end()) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
    }
}

int main(){
    string cards;
    cin >> cards;

    solve_magic_trick(cards);

    return 0;
}