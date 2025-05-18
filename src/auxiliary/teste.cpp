/*
#include <iostream>
#include <vector>
#include <chrono>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include "graph.hpp"
#include "fattest_path.hpp"
#include "ford_fulkerson.hpp"

using namespace std;
using namespace boost;

// Definição de tipos para a implementação do Boost
typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
                      property<edge_capacity_t, long,
                      property<edge_residual_capacity_t, long,
                      property<edge_reverse_t, Traits::edge_descriptor> > > > BoostGraph;
typedef property_map<BoostGraph, edge_capacity_t>::type CapacityMap;
typedef property_map<BoostGraph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<BoostGraph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<BoostGraph>::vertex_descriptor BoostVertex;
typedef graph_traits<BoostGraph>::edge_descriptor BoostEdge;

// Função para adicionar uma aresta bidirecional no grafo do Boost
void addEdge(int from, int to, int capacity,
            BoostGraph& g, 
            CapacityMap& capacitymap, 
            ResidualCapacityMap& residual_capacity, 
            ReverseEdgeMap& reverse_edge) {
    
    BoostEdge e1, e2;
    bool inserted;
    
    tie(e1, inserted) = add_edge(from, to, g);
    tie(e2, inserted) = add_edge(to, from, g);
    
    capacitymap[e1] = capacity;
    capacitymap[e2] = 0;
    
    reverse_edge[e1] = e2;
    reverse_edge[e2] = e1;
}

// Função para gerar um grafo aleatório
Graph generateRandomGraph(BoostGraph& boostGraph, 
                        CapacityMap& capacitymap, ResidualCapacityMap& residual_capacity, 
                        ReverseEdgeMap& reverse_edge, 
                        int numVertices, int numEdges, int maxCapacity) {
    
    srand(time(NULL));
    
    // Limpa os grafos
    Graph myGraph(numVertices);
    
    // Gera arestas aleatórias
    for (int i = 0; i < numEdges; i++) {
        int from = rand() % numVertices;
        int to = rand() % numVertices;
        
        // Evita auto-loops e arestas duplicadas
        if (from == to) continue;
        
        int capacity = 1 + (rand() % maxCapacity);
        
        // Adiciona a aresta na sua implementação
        myGraph.addEdge(from, to, capacity);
        
        // Adiciona a aresta no grafo do Boost
        addEdge(from, to, capacity, boostGraph, capacitymap, residual_capacity, reverse_edge);
    }

    return myGraph;
}

int main() {
    // Parâmetros do teste
    const int numVertices = 100;
    const int numEdges = 500;
    const int maxCapacity = 1000;
    const int source = 0;
    const int sink = numVertices - 1;
    
    // Cria os grafos
    BoostGraph boostGraph(numVertices);
    
    // Obtém os mapas de propriedades do grafo do Boost
    CapacityMap capacitymap = get(edge_capacity, boostGraph);
    ResidualCapacityMap residual_capacity = get(edge_residual_capacity, boostGraph);
    ReverseEdgeMap reverse_edge = get(edge_reverse, boostGraph);
    
    // Gera um grafo aleatório
    Graph myGraph = generateRandomGraph(boostGraph, capacitymap, residual_capacity, reverse_edge, 
                       numVertices, numEdges, maxCapacity);
    
    // Executa sua implementação de fluxo máximo
    auto start1 = chrono::high_resolution_clock::now();
    myGraph.source = source;
    myGraph.sink = sink;
    int myMaxFlow = fordFulkerson(myGraph);
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1).count();
    
    // Executa a implementação de fluxo máximo do Boost
    auto start2 = chrono::high_resolution_clock::now();
    int boostMaxFlow = push_relabel_max_flow(boostGraph, source, sink);
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2).count();
    
    // Imprime os resultados
    cout << "Resultados do teste de fluxo máximo:" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Número de vértices: " << numVertices << endl;
    cout << "Número de arestas: " << numEdges << endl;
    cout << "Capacidade máxima: " << maxCapacity << endl;
    cout << "-----------------------------------" << endl;
    cout << "Sua implementação:" << endl;
    cout << "Fluxo máximo: " << myMaxFlow << endl;
    cout << "Tempo de execução: " << duration1 << " ms" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Implementação do Boost:" << endl;
    cout << "Fluxo máximo: " << boostMaxFlow << endl;
    cout << "Tempo de execução: " << duration2 << " ms" << endl;
    cout << "-----------------------------------" << endl;
    
    if (myMaxFlow == boostMaxFlow) {
        cout << "Resultado: CORRETO! Os fluxos máximos são iguais." << endl;
    } else {
        cout << "Resultado: INCORRETO! Os fluxos máximos diferem." << endl;
    }
    
    return 0;
}
*/