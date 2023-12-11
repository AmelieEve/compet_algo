//
// Created on 11/12/23.
//

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class segment_tree {
    struct node {
        int nb_heads_up = 0;
        int from = 0;
        int to = -1;
        bool pending = false;
        int size() const {
            return to - from + 1;
        }
    };
    std::vector<node> heap;
    int heap_size;
    int array_size;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }
    bool contains(int from1, int to1, int from2, int to2) {
        return from1 <= from2 && to2 <= to1;
    }
    bool intersects(int from1, int to1, int from2, int to2) {
        return (from1 <= from2 && to1 >= from2) ||
               (from1 >= from2 && from1 <= to2);
    }
public:
    segment_tree(int n) {
        array_size = n;
        heap_size = 2 * (1 << ((int)log2(n) + 1));
        heap.resize(heap_size);
        build(1, 0, array_size - 1);
    }

private:
    void build(int heap_index, int from, int to) {
        node& n = heap[heap_index];
        n.from = from;
        n.to = to;
        if (from != to) {
            int middle = from + (to - from) / 2;
            build(left(heap_index), from, middle);
            build(right(heap_index), middle + 1, to);
        }
    }
public:
    int get_nb_heads_up(int from, int to) {
        return get_nb_heads_up(1, from, to);
    }
private:
    int get_nb_heads_up(int heap_index, int from, int to) {
        node& n = heap[heap_index];
        if (!intersects(from, to, n.from, n.to)) return 0;
        if (contains(from, to, n.from, n.to)) return n.nb_heads_up;
        propagate(heap_index);
        return get_nb_heads_up(left(heap_index), from, to) + get_nb_heads_up(right(heap_index), from, to);
    }
public:
    void flip(int from, int to) {
        flip(1, from, to);
    }
private:
    void flip(int heap_index, int from, int to) {
        node& n = heap[heap_index];
        if (contains(from, to, n.from, n.to)) {
            change(n);
        }
        else if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            flip(left(heap_index), from, to);
            flip(right(heap_index), from, to);
            n.nb_heads_up = heap[left(heap_index)].nb_heads_up + heap[right(heap_index)].nb_heads_up;
        }
    }
    void propagate(int heap_index) {
        node& n = heap[heap_index];
        if (n.pending) {
            n.pending = false;
            change(heap[left(heap_index)]);
            change(heap[right(heap_index)]);
        }
    }
    void change(node& n) {
        n.pending = !n.pending;
        n.nb_heads_up = n.size() - n.nb_heads_up;
    }
};

void solve_flipping_coins(int n, vector<vector<int>> &queries) {
    segment_tree segTree = segment_tree(n);

    for (vector<int> query: queries) {
        if(query[0] == 0) {
            segTree.flip(query[1], query[2]);
        } else {
            cout << segTree.get_nb_heads_up(query[1], query[2]) << endl;
        }
    }
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> queries;
    for (int i = 0; i < q; i++) {
        int type, val1, val2;
        cin >> type >> val1 >> val2;
        queries.push_back({type,val1,val2});
    }

    solve_flipping_coins(n, queries);

    return 0;
}