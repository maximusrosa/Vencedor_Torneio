#pragma once
#include "graph.hpp"
#include <queue>

struct State {
    int node;             // vértice atual
    int bottleneck;    // capacidade mínima até aqui (gargalo)

    bool operator<(const State& other) const;
};

bool fattestPath(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path);