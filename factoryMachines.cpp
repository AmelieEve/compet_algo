//
// Created on 29/11/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

void solve_factory_machines2(int t, const vector<int>& ks) {
    int n = ks.size();
    auto possible = [&](ll time) {
        ll res = 0;
        for (int i = 0; i < n; i++) {
            res += time / ks[i];
            if (res >= t) return true;
        }
        return false;
    };
    ll lo = 0, hi = 1e18;
    ll answer = -1;
    while (lo <= hi) {
        ll m = lo + (hi - lo) / 2;
        if (possible(m)) {
            answer = m;
            hi = m - 1;
        } else {
            lo = m + 1;
        }
    }
    cout << answer << endl;
}

int main() {
    int n, t;
    cin >> n >> t;
    vector<int> machinesEfficiency;
    for(int i = 0; i < n; i++) {
        int efficiency;
        cin >> efficiency;
        machinesEfficiency.push_back(efficiency);
    }

    solve_factory_machines2(t, machinesEfficiency);
    return 0;
}

#if 0
int tot_products(int instant, vector<int> &machinesEfficiency) {
    int sum = 0;
    for(int machineEff: machinesEfficiency) {
        sum += (instant/machineEff);
    }
    return sum;
}

int new_products(int instant, vector<int> &machinesEfficiency) {
    int sum = 0;
    for(int machineEff: machinesEfficiency) {
        if(instant%machineEff == 0) {
            sum+=1;
        }
    }
    return sum;
}

void solve_factory_machines(int t, vector<int> &machinesEfficiency) {
    int min = 1;
    int max = t*(*min_element(machinesEfficiency.begin(), machinesEfficiency.end()));
    if(max == 1) {
        cout << 1 << endl;
        return;
    }

    int middle = (max + min)/2;
    int producedMiddle = tot_products(middle, machinesEfficiency);

    while(producedMiddle != t) {
        if(max == min+1) {
            middle = max;
            break;
        } else if(producedMiddle < t) {
            min = middle;
            middle = (max+min)/2;
        } else {
            max = middle;
            middle = (max+min)/2;
        }
        producedMiddle = tot_products(middle, machinesEfficiency);
    }
    cout << middle << endl;
}
#endif