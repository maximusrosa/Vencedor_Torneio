#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <sstream>
#include <fstream>
#include <algorithm>
#define INF INT_MAX

using namespace std;

struct Edge {
    int from; // talvez não precise
    int to;
    int capacity;
    int flow;
    Edge* residual;

    Edge(int from, int to, int capacity);

    int residualCapacity() const;
    void augment(int bottleneck);
};

class Graph {
private:
    int numVertices;
    int numEdges;
    vector<vector<Edge*>> adjVector;

public:
    int source;
    int sink;
    
    Graph(int numVertices);
    Graph(istream& in);

    ~Graph();

    int getNumVertices() const;
    int getNumEdges() const;
    int getNumResidualEdges() const;
    const vector<Edge*>& getAdjList(int u) const;

    void addEdge(int u, int v, int capacity);

    void printGraph() const;
};
