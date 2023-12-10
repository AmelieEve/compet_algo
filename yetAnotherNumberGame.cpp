#include <iostream>
using namespace std;

string playTestCase(int n) {
    if(n % 2 == 0)
    {
        return "ALICE";
    }
    else
    {
        return "BOB";
    }
}

int main() {
    int tc;
    cin >> tc;
    
    for(int i=0; i<tc; i++)
    {
        int n;
        cin >> n;
        cout << playTestCase(n) << endl;
    }
	return 0;
}
