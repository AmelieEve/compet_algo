//
// Created on 10/11/23.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve_sum_of_three_values(int n, int x, vector<pair<int, int>> values) {
    for (int i = 0; i < n - 1; i++) {
        int start = i+1;
        int end = n-1;
        int target = x - values[i].first;

        while(start < end) {
            int sum = values[start].first + values[end].first;
            if(sum == target) {
                cout << values[start].second << " " << values[i].second << " " << values[end].second << endl;
                return 0;
            }
            else if(sum > target) {
                end--;
            }
            else {
                start++;
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}

int main() {
    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> values;
    int v;
    for(int i = 0; i < n; i++) {
        cin >> v;
        values.push_back({v,i+1});
    }

    sort(values.begin(), values.end());

    solve_sum_of_three_values(n,x,values);

    return 0;
}

#if 0
void solve_sum_of_three_values(int x, vector<int> &terms, vector<int> &res) {
    if(terms.size() < 3) return;
    vector<int> sortedTerms(terms);
    sort(sortedTerms.begin(), sortedTerms.end());

    function<void(int,int,int,int)> solve = [&](int sum, int k1, int k2, int k3) {
        if (k1 >= sortedTerms.size() - 2) return;
        int attemptSum = sortedTerms[k1] + sortedTerms[k2] + sortedTerms[k3];
        if (attemptSum == sum) {
            auto res0 = find(terms.begin(), terms.end(), sortedTerms[k1]);

            auto beginFindRes1 = terms.begin();
            if (sortedTerms[k1] == sortedTerms[k2]) {
                beginFindRes1 = res0 + 1;
            }
            auto res1 = find(beginFindRes1, terms.end(), sortedTerms[k2]);

            auto beginFindRes2 = terms.begin();
            if (sortedTerms[k1] == sortedTerms[k3]) {
                if (sortedTerms[k2] == sortedTerms[k3]) {
                    beginFindRes2 = res1 + 1;
                } else {
                    beginFindRes2 = res0 + 1;
                }
            } else if (sortedTerms[k2] == sortedTerms[k3]) {
                beginFindRes2 = res1 + 1;
            }
            auto res2 = find(beginFindRes2, terms.end(), sortedTerms[k3]);

            res[0] = (int) distance(terms.begin(), res0) + 1;
            res[1] = (int) distance(terms.begin(), res1) + 1;
            res[2] = (int) distance(terms.begin(), res2) + 1;
            sort(res.begin(), res.end());
            return;
        } else if(k3 == k2+1) {
            solve(sum, k1+1, k1+2, (int)sortedTerms.size()-1);
        } else if(attemptSum > sum) {
            solve(sum, k1, k2, k3-1);
        } else {
            solve(sum, k1, k2+1, k3);
        }
    };

    return solve(x,0,1,(int)terms.size() - 1);
}

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> possibleSumTerms;
    for(int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        possibleSumTerms.push_back(ai);
    }

    vector<int> res(3,-1);
    solve_sum_of_three_values(x, possibleSumTerms, res);
    for(int k = 0; k < res.size(); k++) {
        if(res[0] == -1) {
            cout << "IMPOSSIBLE";
            break;
        } else {
            cout << res[k];
            if(k < res.size() - 1) cout << " ";
        }
    }
    cout << endl;

    return 0;
}
#endif

#if 0
void solve_sum_of_three_values_beta(int x, vector<int> &terms, vector<int> &res) {
    if(terms.size() < 3) return;
    vector<int> sortedTerms(terms);
    sort(sortedTerms.begin(), sortedTerms.end());

    function<void(int,int,int,int)> solve = [&](int sum, int k1, int k2, int k3) {
        if(k3 >= sortedTerms.size()) return;
        int attemptSum = sortedTerms[k1]+sortedTerms[k2]+sortedTerms[k3];
        if(attemptSum == sum) {
            auto res0 = find(terms.begin(), terms.end(), sortedTerms[k1]);

            auto beginFindRes1 = terms.begin();
            if(sortedTerms[k1] == sortedTerms[k2]) {
                beginFindRes1 = res0+1;
            }
            auto res1 = find(beginFindRes1, terms.end(), sortedTerms[k2]);

            auto beginFindRes2 = terms.begin();
            if(sortedTerms[k1] == sortedTerms[k3]) {
                if(sortedTerms[k2] ==  sortedTerms[k3]) {
                    beginFindRes2 = res1 + 1;
                } else {
                    beginFindRes2 = res0 + 1;
                }
            } else if(sortedTerms[k2] == sortedTerms[k3]) {
                beginFindRes2 = res1+1;
            }
            auto res2 = find(beginFindRes2, terms.end(), sortedTerms[k3]);

            res[0] = (int)distance(terms.begin(), res0) + 1;
            res[1] = (int)distance(terms.begin(), res1) + 1;
            res[2] = (int)distance(terms.begin(), res2) + 1;
            sort(res.begin(), res.end());
            return;
        } else if(attemptSum > sum) {
            return;
        } else {
            if(k3 < sortedTerms.size() - 1) {
                solve(sum, k1, k2, k3+1);
            } else if(k2 < sortedTerms.size() - 2) {
                solve(sum, k1, k2+1, k2+2);
            } else if(k1 < sortedTerms.size() - 3) {
                solve(sum, k1+1, k1+2, k1+3);
            } else {
                return;
            }
        }
    };

    return solve(x,0,1,2);
}
#endif