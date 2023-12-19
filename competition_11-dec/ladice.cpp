//
// Created on 11/12/23.
//

#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

bool tryMoveFrom(int item, int drawer, vector<int> &insideDrawers, vector<pair<int,int>> &possibleDrawers, vector<int> &testedDrawers) {
    int annoyingItem = insideDrawers[drawer];
    int otherDrawerForAnnoyingItem = possibleDrawers[annoyingItem].first != drawer ? possibleDrawers[annoyingItem].first : possibleDrawers[annoyingItem].second;
    if(testedDrawers[otherDrawerForAnnoyingItem] == 1) {
        return false;
    }
    testedDrawers[otherDrawerForAnnoyingItem] = 1;

    if(insideDrawers[otherDrawerForAnnoyingItem] == -1 || tryMoveFrom(annoyingItem, otherDrawerForAnnoyingItem, insideDrawers, possibleDrawers, testedDrawers)) {
        insideDrawers[otherDrawerForAnnoyingItem] = annoyingItem;
        insideDrawers[drawer] = item;
        return true;
    }
    return false;
}

void solve_ladice(int n, int l, vector<pair<int,int>> &possibleDrawers) {
    vector<int> insideDrawers(l, -1);
    for(int i = 0; i < n; i++) {
        int drawerA = possibleDrawers[i].first;
        int drawerB = possibleDrawers[i].second;

        string res = "LADICA";

        cerr << "in A : " << insideDrawers[drawerA] << "; in B : " << insideDrawers[drawerB] << endl;
        if(insideDrawers[drawerA] == -1) { // rule 1
            insideDrawers[drawerA] = i;
        } else if(insideDrawers[drawerB] == -1) { // rule 2
            insideDrawers[drawerB] = i;
        } else {
            vector<int> testedDrawers(l,0);
            if(!tryMoveFrom(i, drawerA, insideDrawers, possibleDrawers, testedDrawers) // rule 3
                && !tryMoveFrom(i, drawerB, insideDrawers, possibleDrawers, testedDrawers)) { // rule 4
                res = "SMECE";
            }
        }

        cout << res << endl;
    }
}

int main(){
    int n, l;
    cin >> n >> l;

    vector<pair<int,int>> possibleDrawers;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        possibleDrawers.push_back({a,b});
    }

    solve_ladice(n, l, possibleDrawers);

    return 0;
}