#ifndef MST_H
#define MST_H

#include <vector>
#include <queue>
#include <algorithm>
#include "grafo.h"
#include "union_find.h"

/**
 * IMPLEMENTACIÓN DEL ALGORITMO DE KRUSKAL
 */
std::vector<Arista> kruskal(GrafoLista& G) {
    std::vector<Arista> E_T;
    
    // Ordenar E de forma no decreciente con respecto al peso de las aristas
    std::vector<Arista> aristas = G.todasLasAristas;
    std::sort(aristas.begin(), aristas.end());

    // Inicializar la estructura Union-Find para el control de aciclicidad
    UnionFind uf(G.numVertices);
    size_t k = 0;

    // Ciclo principal: mientras |ET| < |V| - 1
    while (E_T.size() < (size_t)(G.numVertices - 1) && k < aristas.size()) {
        Arista e_k = aristas[k];
        k++;

        // Condición: si ET U {ek} es acíclico
        if (uf.buscar(e_k.u) != uf.buscar(e_k.v)) {
            uf.unir(e_k.u, e_k.v); // ET <- ET U {ek}
            E_T.push_back(e_k);
        }
    }

    return E_T;
}

/**
 * IMPLEMENTACIÓN DEL ALGORITMO DE PRIM
 * Utiliza una cola de prioridad para simular la selección de la arista mínima.
 */
std::vector<Arista> prim(GrafoLista& G) {
    std::vector<Arista> E_T;
    std::vector<bool> en_VT(G.numVertices, false);

    // Configuración de la cola de prioridad de C++ como un min-heap
    auto comp = [](const Arista& a, const Arista& b) { return a.peso > b.peso; };
    std::priority_queue<Arista, std::vector<Arista>, decltype(comp)> pq(comp);

    // VT <- {v0}. Comenzamos de forma determinista en el vértice 0
    int v0 = 0;
    en_VT[v0] = true;

    // Insertar a la cola todas las aristas adyacentes al nodo inicial
    for (const auto& vecino : G.listas[v0]) {
        pq.push({v0, vecino.first, vecino.second});
    }

    // El ciclo se repite exactamente |V| - 1 veces para añadir las aristas del MST
    for (int i = 1; i < G.numVertices; ++i) {
        Arista e_star;
        bool encontrada = false;

        // Encontrar una arista de peso mínimo e* entre u en VT y v en V \ VT
        while (!pq.empty()) {
            Arista top = pq.top();
            pq.pop();

            // Verificar si conecta un nodo de VT con uno fuera de VT
            if (en_VT[top.u] != en_VT[top.v]) {
                e_star = top;
                encontrada = true;
                break;
            }
        }

        // Si el grafo no es conexo, salimos antes para evitar ciclos infinitos
        if (!encontrada) break;

        // Determinar cuál es el nuevo vértice v* que entra a VT
        int v_star = (!en_VT[e_star.u]) ? e_star.u : e_star.v;
        
        // VT <- VT U {v*} y ET <- ET U {e*}
        en_VT[v_star] = true;
        E_T.push_back(e_star);

        // Añadir a la cola las nuevas aristas candidatas que ofrece el vértice v*
        for (const auto& vecino : G.listas[v_star]) {
            if (!en_VT[vecino.first]) {
                pq.push({v_star, vecino.first, vecino.second});
            }
        }
    }

    return E_T;
}

#endif
