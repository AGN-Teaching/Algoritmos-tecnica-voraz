#ifndef GENERADOR_H
#define GENERADOR_H

#include "grafo.h"
#include <random>
#include <set>

// Genera un GrafoLista con densidad controlada
GrafoLista generarGrafo(int V, bool esDenso) {
    GrafoLista G(V);
    
    // Calcular cuántas aristas totales debe tener el grafo
    long long aristasObjetivo = esDenso ? ((long long)V * V / 4) : (2LL * V);
    
    // Para evitar duplicar aristas (u, v) usamos un set ordenando el par menor-mayor
    std::set<std::pair<int, int>> aristasExistentes;
    std::mt19937 rng(1337);
    std::uniform_int_distribution<int> distPeso(1, 100);
    std::uniform_int_distribution<int> distNodo(0, V - 1);

    // Garantizar conectividad
    for (int i = 0; i < V - 1; ++i) {
        int peso = distPeso(rng);
        G.agregarArista(i, i + 1, peso);
        aristasExistentes.insert({i, i + 1});
    }

    // Rellenar con aristas aleatorias
    long long aristasActuales = V - 1;
    while (aristasActuales < aristasObjetivo) {
        int u = distNodo(rng);
        int v = distNodo(rng);

        if (u != v) {
            int menor = std::min(u, v);
            int mayor = std::max(u, v);

            // Si la arista no existe, la añadimos
            if (aristasExistentes.find({menor, mayor}) == aristasExistentes.end()) {
                int peso = distPeso(rng);
                G.agregarArista(u, v, peso);
                aristasExistentes.insert({menor, mayor});
                aristasActuales++;
            }
        }
    }
    return G;
}

// Conveirte un GrafoLista a GrafoMatriz para los experimentos de Dijkstra
GrafoMatriz convertirAMatriz(const GrafoLista& gLista) {
    GrafoMatriz gMatriz(gLista.numVertices);
    for (const auto& arista : gLista.todasLasAristas) {
        gMatriz.agregarArista(arista.u, arista.v, arista.peso);
    }
    return gMatriz;
}

#endif
