#include "fattest_path.hpp"
#include "max_heap.hpp"

bool State::operator<(const State& other) const {
    return bottleneck < other.bottleneck;
}

bool fattestPath(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path) {
    int n = g.getNumVertices();
    vector<Edge*> parent(n, nullptr);
    vector<int> bottleneck(n, 0);
    vector<bool> inQueue(n, false); // Track which nodes are in the queue

    MaxHeap maxHeap(n);
    
    bottleneck[source] = INF;
    maxHeap.insert(source, bottleneck[source]);
    visited[source] = true;
    inQueue[source] = true; // Mark source as in queue

    while (!maxHeap.isEmpty()) {
        pair<int, int> curr = maxHeap.extractMax();
        int u = curr.first;  // node
        int currBottleneck = curr.second;  // bottleneck value
        
        inQueue[u] = false; // Node is no longer in queue
        
        if (currBottleneck < bottleneck[u]) {
            // Skip outdated entries in the priority queue
            continue;
        }
        
        if (u == sink) {
            // Reconstruct path
            int v = sink;
            while (v != source) {
                Edge* e = parent[v];
                path.push_back(e);
                v = e->from;
            }
            reverse(path.begin(), path.end());
            
            return true;
        }
        
        for (Edge* e : g.getAdjList(u)) {
            if (e->residualCapacity() <= 0) continue;
            
            int v = e->to;
            int newBottleneck = min(bottleneck[u], e->residualCapacity());
            
            if (newBottleneck > bottleneck[v]) {
                bottleneck[v] = newBottleneck;
                parent[v] = e;
                
                // Check if this is a new insertion or an update
                if (!inQueue[v]) {
                    // New insertion
                    maxHeap.insert(v, newBottleneck);
                    inQueue[v] = true;
                } else {
                    // Update - use increaseKey em vez de reinserir
                    maxHeap.increaseKey(v, newBottleneck);
                }
            }
        }
    }
    
    return false;
}