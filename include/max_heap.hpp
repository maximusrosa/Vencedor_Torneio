#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class MaxHeap {
private:
    int n; // Max number of nodes
    int k; // Number of children per node
    vector<pair<int, int>> heap; // {vertex, distance}
    unordered_map<int, int> position; // Maps vertex -> heap index

    int parent(int i);
    int child(int i, int j);
    void restoreDown(int index);
    void restoreUp(int index);
    void swapNodes(int i, int j);

public:
    MaxHeap(int n, int k);
    MaxHeap(int n); // Default to 8-ary heap
    bool isEmpty();
    void insert(int vertex, int distance);
    pair<int, int> extractMax();
    bool contains(int vertex);
    void increaseKey(int vertex, int distance);
    void printHeap();
};