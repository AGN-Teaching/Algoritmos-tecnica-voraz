#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <queue>
#include "grafo.h"

// Valor muy grande para representar el infinito
const int INF_DIST = 1e9;

/**
 * DIJKSTRA LINEAL (Matriz de adyacencia)
 * Complejidad teórica: O(|V|^2)
 * Busca el nodo mínimo escaneando un arreglo de tamaño |V| en cada iteración.
 */
std::vector<int> dijkstraLineal(GrafoMatriz& G, int origen) {
    int V = G.numVertices;
    std::vector<int> distancia(V, INF_DIST);
    std::vector<bool> visitado(V, false);

    // La distancia del nodo origen a sí mismo es siempre 0
    distancia[origen] = 0;

    for (int i = 0; i < V - 1; ++i) {
        // Encontrar el vértice con la distancia mínima de los no procesados
        int u = -1;
        int min_dist = INF_DIST;
        
        for (int v = 0; v < V; ++v) {
            if (!visitado[v] && distancia[v] < min_dist) {
                min_dist = distancia[v];
                u = v;
            }
        }

        // Si no se encontró un nodo alcanzable, terminamos (grafo disconexo)
        if (u == -1) break;

        // Marcar el vértice seleccionado como procesado
        visitado[u] = true;

        // Actualizar las distancias de los vértices adyacentes al nodo 'u'
        for (int v = 0; v < V; ++v) {
            if (!visitado[v] && G.matriz[u][v] != G.INF) {
                int nueva_dist = distancia[u] + G.matriz[u][v];
                if (nueva_dist < distancia[v]) {
                    distancia[v] = nueva_dist;
                }
            }
        }
    }

    return distancia;
}

/**
 * DIJKSTRA CON MIN-HEAP (Lista de adyacencia)
 * Complejidad teórica: O(|E| log |V|)
 * Optimiza la búsqueda del nodo mínimo utilizando la cola de prioridad de C++.
 */
std::vector<int> dijkstraHeap(GrafoLista& G, int origen) {
    int V = G.numVertices;
    std::vector<int> distancia(V, INF_DIST);
    
    // Configuración del Min-Heap guardando pares de (distancia, nodo)
    // El contenedor ordena automáticamente de menor a mayor distancia
    using Pair = std::pair<int, int>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

    // Inicializar origen
    distancia[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        // Extraer el nodo con la distancia mínima actual
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Si ya encontramos un camino más corto hacia 'u', ignoramos este registro anterior
        if (d > distancia[u]) continue;

        // Relajar las aristas vecinas del nodo 'u'
        for (const auto& vecino : G.listas[u]) {
            int v = vecino.first;
            int peso = vecino.second;

            if (distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
                pq.push({distancia[v], v});
            }
        }
    }

    return distancia; 
}

#endif
