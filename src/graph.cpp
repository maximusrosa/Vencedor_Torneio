#include "graph.hpp"

Edge::Edge(int from, int to, int capacity) : from(from), to(to), capacity(capacity), flow(0), residual(nullptr) {}

int Edge::residualCapacity() const {
    return capacity - flow;
}

void Edge::augment(int bottleneck) {
    flow += bottleneck;
    residual->flow -= bottleneck;
}


Graph::Graph(int numVertices)
    : numVertices(numVertices), numEdges(0), adjVector(numVertices) {}

Graph::Graph(istream& in) {
    string line, dummy;
    unsigned n = 0, m = 0;

    while (getline(in, line)) {
        if (line.substr(0, 5) == "p max") {  // Aceita 'p max'
            stringstream linestr(line);
            linestr >> dummy >> dummy >> n >> m;
            numVertices = n;
            numEdges = m;
            adjVector.resize(n);
        }
        else if (line.substr(0, 2) == "n ") { // Lê source e sink
            stringstream nodestr(line);
            char nc;
            unsigned v;
            string role;
            nodestr >> nc >> v >> role;
            v--; // índice começa de 0
            if (role == "s")
                source = v;
            else if (role == "t")
                sink = v;
        }
        else if (line.substr(0, 2) == "a ") { // Lê arestas
            if (adjVector.empty()) {
                cerr << "Erro: encontrou aresta antes de definir 'p max'." << endl;
                exit(1);
            }

            stringstream arc(line);
            char ac;
            unsigned u, v, w;
            arc >> ac >> u >> v >> w;
            u--; v--; // índice 0-based
            addEdge(u, v, w);
        }
        // ignora linhas começando com 'c'
    }
}

Graph::~Graph() {
    for (auto& edges : adjVector) {
        for (Edge* e : edges) {
            delete e;
        }
    }
}

int Graph::getNumVertices() const {
    return numVertices;
}

int Graph::getNumEdges() const {
    return numEdges;
}

int Graph::getNumResidualEdges() const {
    return numEdges * 2; // cada aresta tem uma aresta residual (aproximadamente)
}

const vector<Edge*>& Graph::getAdjList(int u) const {
    return adjVector[u];
}

void Graph::addEdge(int u, int v, int capacity) {
    Edge* uv = new Edge(u, v, capacity);
    Edge* vu = new Edge(v, u, 0); // arco residual

    uv->residual = vu;
    vu->residual = uv;

    adjVector[u].push_back(uv);
    adjVector[v].push_back(vu);
}

void Graph::printGraph() const {
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << ": ";
        for (const auto& edge : adjVector[i]) {
            cout << "(" << edge->to << ", " << edge->capacity << ") ";
        }
        cout << endl;
    }
}

