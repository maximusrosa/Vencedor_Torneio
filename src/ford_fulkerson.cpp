#include "ford_fulkerson.hpp"

void printPath(const vector<Edge*>& path, int pathFlow) {
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i]->from;
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\n";

    cout << ", Flow: " << pathFlow << "\n";
}

int fordFulkerson(Graph& g) { 
    vector<Edge*> path;
    vector<bool> visited;
    int numVertices = g.getNumVertices();
    int maxFlow = 0;

    int numIterations = 0;
    while (true) {
        numIterations++;

        visited.assign(numVertices, false);

        path.clear();

        if (!fattestPath(g, g.source, g.sink, visited, path)) break; 
    
        int pathFlow = INF;
        for (Edge* e : path) {
            pathFlow = min(pathFlow, e->residualCapacity()); // bottleneck
        }

        for (Edge* e : path) {
            e->augment(pathFlow);
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}



