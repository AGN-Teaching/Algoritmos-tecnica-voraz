#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>

// Estructura para representar una arista ponderada
struct Arista {
    int u, v;
    int peso;

    // Operador para poder ordenar aristas en Kruskal
    bool operator<(const Arista& otra) const {
        return peso < otra.peso;
    }
};


// REPRESENTACIÓN POR MATRIZ DE ADYACENCIA
class GrafoMatriz {
public:
    int numVertices;
    std::vector<std::vector<int>> matriz;
    const int INF = 1e9; // Valor para infinito (ausencia de arista)

    GrafoMatriz(int vertices) : numVertices(vertices) {
        matriz.assign(vertices, std::vector<int>(vertices, INF));
        for(int i = 0; i < vertices; ++i) matriz[i][i] = 0;
    }

    void agregarArista(int u, int v, int peso) {
        matriz[u][v] = peso;
        matriz[v][u] = peso;
    }
};



// REPRESENTACIÓN POR LISTAS DE ADYACENCIA
class GrafoLista {
public:
    int numVertices;
    // Pares de (nodo_destino, peso)
    std::vector<std::vector<std::pair<int, int>>> listas;
    std::vector<Arista> todasLasAristas; // Utilidad para Kruskal

    GrafoLista(int vertices) : numVertices(vertices) {
        listas.resize(vertices);
    }

    void agregarArista(int u, int v, int peso) {
        listas[u].push_back({v, peso});
        listas[v].push_back({u, peso}); // Grafo no dirigido
        todasLasAristas.push_back({u, v, peso});
    }
};

#endif
