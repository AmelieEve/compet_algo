//
// Created by amelie on 06/11/23.
//
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class union_find
{
    vector<int> id; //id[i] = parent of i
    vector<int> sz; //sz[i] = number of objects in subtree rooted at i
    int count;      //number of components
public:
    union_find(int N) : id(N, 0), sz(N, 1) {
        count = N;
        for (int i = 0; i < N; i++) {
            id[i] = i;
        }
    }

    int nb_components() {
        return count;
    }

    int size_set(int i) {
        return sz[find_set(i)];
    }

    int find_set(int i) {
        return (id[i] == i) ? i : (id[i] = find_set(id[i]));
    }

    bool connected(int i, int j) {
        return find_set(i) == find_set(j);
    }

    void union_set(int p, int q) {
        int i = find_set(p);
        int j = find_set(q);
        if (i == j) return;
        // make smaller root point to larger one
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        }
        else {
            id[j] = i;
            sz[i] += sz[j];
        }
        --count;
    }
};


int main() {
    int tc;
    cin >> tc;

    for(int i=0; i<tc; i++)
    {
        int f;
        cin >> f;
        map<string,int> people;
        int max_people = 2*f;
        union_find uf(max_people);
        while(f-- > 0)
        {
            string f1, f2;
            cin >> f1 >> f2;
            if(people.find(f1) == people.end())
            {
                people[f1] = (int)people.size();
            }
            if(people.find(f2) == people.end())
            {
                people[f2] = (int)people.size();
            }
            uf.union_set(people[f1], people[f2]);
            cout << max(uf.size_set(people[f1]), uf.size_set(people[f2])) << endl;
        }
    }
    return 0;
}