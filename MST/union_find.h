#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>

class UnionFind {
private:
    std::vector<int> padre;
    std::vector<int> rango;

public:
    UnionFind(int n) {
        padre.resize(n);
        rango.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            padre[i] = i; // Al inicio, cada nodo es su propio padre
        }
    }

    // Buscar el representante del conjunto (con compresión de caminos)
    int buscar(int i) {
        if (padre[i] == i)
            return i;
        return padre[i] = buscar(padre[i]); // Compresión
    }

    // Unir dos conjuntos utilizando el rango
    bool unir(int i, int j) {
        int raiz_i = buscar(i);
        int raiz_j = buscar(j);

        if (raiz_i != raiz_j) {
            // El árbol más bajo se "cuelga" del más alto
            if (rango[raiz_i] < rango[raiz_j]) {
                padre[raiz_i] = raiz_j;
            } else if (rango[raiz_i] > rango[raiz_j]) {
                padre[raiz_j] = raiz_i;
            } else {
                padre[raiz_j] = raiz_i;
                rango[raiz_i]++;
            }
            return true; // Se pudo realizar la unión (no había ciclo)
        }
        return false; // Ya pertenecían al mismo conjunto (detectó un ciclo)
    }
};

#endif
