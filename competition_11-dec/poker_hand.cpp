//
// Created on 11/12/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void solve_poker_hand(vector<string> &cards) {
    map<char,int> ranks;
    for(auto & card : cards) {
        ++ranks[card[0]];
    }
    auto strength = max_element(ranks.begin(),ranks.end(), [] (const pair<char,int> & p1, const pair<char,int> & p2) {
        return p1.second < p2.second;
    });
    cout << strength->second << endl;
}

int main() {
    vector<string> cards;
    for(int i = 0; i < 5; i++) {
        string card;
        cin >> card;
        cards.push_back(card);
    }

    solve_poker_hand(cards);

    return 0;
}