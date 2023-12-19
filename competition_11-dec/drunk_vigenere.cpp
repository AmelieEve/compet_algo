//
// Created on 11/12/23.
//

#include <iostream>
using namespace std;

void solve_drunk_vigenere(string &encrypted, string &key) {
    int n = encrypted.size();

    string decrypted;
    for(int i = 0; i < n; i++) {
        int shift = (key[i] - 'A');
        char newLetter;
        if(i%2 != 0) {
            if(encrypted[i] + shift > 'Z') {
                shift -= ('Z' - encrypted[i] + 1);
                newLetter = 'A' + shift;
            } else {
                newLetter = encrypted[i] + shift;
            }
            decrypted += newLetter;
        } else {
            if(encrypted[i] - shift < 'A') {
                shift -= (encrypted[i] - 'A' + 1);
                newLetter = 'Z' - shift;
            } else {
                newLetter = encrypted[i] - shift;
            }
            decrypted += newLetter;
        }
    }
    cout << decrypted << endl;
}

int main() {
    string encrypted, key;
    cin >> encrypted >> key;

    solve_drunk_vigenere(encrypted, key);

    return 0;
}