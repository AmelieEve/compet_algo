//
// Created on 10/12/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve_exams(vector<int> &exams, vector<int> &preparations) {
    int n = exams.size();
    int m = preparations.size();

    // There will be at least m days on which Vasiliy passes exams, plus the total time needed to prepare all these exams.
    int lower_min = m;
    for(int time: preparations) {
        lower_min += time;
    }

    auto possible = [&](int nb_days) {
        vector<int> positions(n);
        for (int i = 0; i < nb_days; ++i) {
            positions[exams[i]] = i; // We store the position of an exam, because we can only have one exam a day
                                    // we try to put a given exam as far as possible to have more time to prepare
        }
        positions[0] = -1; // Zero is not a valid exam number
        int prep = 0;
        int nb_exams = 0;
        for (int i = 0; i < nb_days; ++i) {
            if (positions[exams[i]] == i) {
                ++nb_exams; // If exams[i] is at position i we need to check if we have had enough time to prepare
                if (prep < preparations[exams[i]]) return false;
                prep -= preparations[exams[i]];
            } else {
                ++prep;
            }
        }
        return nb_exams == m;
    };

    int lo = lower_min, hi = n;
    int answer = -1;
    while (lo <= hi) {
        int middle = lo + (hi - lo) / 2;
        if (possible(middle)) {
            answer = middle;
            hi = middle - 1;
        } else {
            lo = middle + 1;
        }
    }
    cout << answer << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> exams;
    for(int i = 0; i < n; i++) {
        int exam;
        cin >> exam;
        exams.push_back(exam);
    }
    vector<int> preparations;
    for(int i = 0; i < m; i++) {
        int time;
        cin >> time;
        preparations.push_back(time);
    }

    solve_exams(exams, preparations);
    return 0;
}