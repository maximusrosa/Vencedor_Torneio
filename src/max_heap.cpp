#include "max_heap.hpp"

int MaxHeap::parent(int i) { return (i - 1) / k; }

int MaxHeap::child(int i, int j) { return k * i + (j + 1); }

void MaxHeap::restoreDown(int index) {
    while (true) {
        int max_child_index = -1; 

        for (int j = 0; j < k; j++) {
            int c = child(index, j);
            if (c < heap.size() && (max_child_index == -1 || heap[c].second > heap[max_child_index].second)) {  
                max_child_index = c;
            }
        }

        if (max_child_index == -1 || heap[index].second >= heap[max_child_index].second)  
            break;

        swapNodes(index, max_child_index);
        index = max_child_index;
    }
}

void MaxHeap:: restoreUp(int index) {
    while (index > 0 && heap[parent(index)].second < heap[index].second) {  
        swapNodes(index, parent(index));
        index = parent(index);
    }
}

void MaxHeap:: swapNodes(int i, int j) {
    swap(heap[i], heap[j]);
    position[heap[i].first] = i;
    position[heap[j].first] = j;
}


MaxHeap::MaxHeap(int n, int k) : n(n), k(k) {}  

MaxHeap::MaxHeap(int n): n(n), k(8) {} 

bool MaxHeap::isEmpty() { return heap.empty(); }

void MaxHeap::insert(int vertex, int distance) {
    pair<int, int> node = {vertex, distance};
    heap.push_back(node);

    int index = heap.size() - 1;
    position[node.first] = index;

    restoreUp(index);
}

pair<int, int> MaxHeap::extractMax() {  
    if (heap.empty()) throw runtime_error("Heap is empty");

    pair<int, int> maxVal = heap[0];  
    position.erase(maxVal.first);

    if (heap.size() > 1) {
        heap[0] = heap.back();
        position[heap[0].first] = 0;
    }

    heap.pop_back();

    restoreDown(0);

    return maxVal; 
}

bool MaxHeap::contains(int vertex) {
    return position.find(vertex) != position.end();
}

void MaxHeap::increaseKey(int vertex, int newDist) {  
    if (position.find(vertex) == position.end()) return;

    int index = position[vertex];

    if (heap[index].second < newDist) {  
        heap[index].second = newDist;
        restoreUp(index);
    }
}

void MaxHeap::printHeap() {
    int level = 0;
    int nodesInLevel = 1;
    int count = 0;

    for (const auto& [vertex, dist] : heap) {
        cout << "(" << vertex << ", " << dist << ") ";
        count++;

        if (count == nodesInLevel) {
            cout << endl;
            level++;
            nodesInLevel *= k;
            count = 0;
        }
    }

    if (count > 0) {
        cout << endl;
    }
}
