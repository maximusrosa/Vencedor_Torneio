#pragma once
#include "graph.hpp"
#include "fattest_path.hpp"
#include <chrono>
#include <math.h>

using namespace chrono;

typedef bool (*AugPathFinder)(Graph&, int, int, vector<bool>&, vector<Edge*>&); // algoritmo de busca de caminho aumentante

void printPath(const vector<Edge*>& path, int pathFlow);

int fordFulkerson(Graph& g);