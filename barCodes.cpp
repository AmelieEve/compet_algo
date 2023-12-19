//
// Created on 19/12/23.
//

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_DIM = 60;
long memo[MAX_DIM][MAX_DIM];

long solve_bar_codes(int n, int k, int m)
{
    if (n < 0) return 0;
    if (n == 0)
    {
        if (k == 0) return 1;
        return 0;
    }
    if (k <= 0) return 0;
    if (memo[n][k] != -1) return memo[n][k];
    long res = 0;
    for (int i = 1; i <= m; ++i)
    {
        res += solve_bar_codes(n - i, k - 1, m);
    }
    return memo[n][k] = res;
}


int main() {
    int n, k, m;
    while (cin >> n >> k >> m)
    {
        memset(memo, -1, sizeof(memo));
        cout << solve_bar_codes(n, k, m) << endl;
    }
    return 0;

    return 0;
}

/*
Pour n >= 1 :
ceil(n/k) <= m <= n
1 <= k <= n

1 1 1
1
-----------
2 1 2
11

2 2 1/2
10
-----------
3 1 3
111

3 2 2
110
100

3 2 3
110
100
111

3 3 1/2/3
101
-----------
4 1 4
1111

4 2 2
1100

4 2 3
1100
1110
1000

4 2 4
1100
1110
1000

4 3 2
1101
1001
1011

4 3 3
1011
1101
1001

4 3 4


4 4 1/2/3/4
1010
 */