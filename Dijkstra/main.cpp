#include <iostream>
#include <fstream>
#include <vector>
#include "grafo.h"
#include "generador.h"
#include "dijkstra.h"
#include "tiempoejecucion.h"


void ejecutarExperimentoDijkstra() {
    // Abrir el archivo para escribir los resultados
    std::ofstream archivo("dijkstra_tiempos.csv");
    if (!archivo.is_open()) {
        std::cerr << "ERROR: No se pudo crear el archivo dijkstra_tiempos.csv\n";
        return;
    }

    std::cout << "Iniciando toma de tiempos para Dijkstra (Lineal vs Heap)...\n";
    
    // Escribir la cabecera del archivo CSV
    archivo << "Vertices,Aristas,Tipo,TiempoLineal,TiempoHeap\n";

    // Tamaños de control incrementales para los grafos (|V|)
    std::vector<int> tamanos = {1000, 2000, 3000, 4000, 5000};

    // Nodo origen fijo para realizar las rutas
    const int nodo_origen = 0;

    for (int V : tamanos) {
        std::cout << "Procesando |V| = " << V << "..." << std::endl;

        // =====================================================================
        // --- EVALUACIÓN EN GRAFO DISPERSO (|E| ≈ 2|V|) ---
        // =====================================================================
        GrafoLista gListaDisperso = generarGrafo(V, false);
        GrafoMatriz gMatrizDisperso = convertirAMatriz(gListaDisperso);
        long long E_disp = gListaDisperso.todasLasAristas.size();

        // Medir Dijkstra Lineal (Matriz) en milisegundos (ms)
        double time_lineal_disp = medir_tiempo_ejecucion(dijkstraLineal, gMatrizDisperso, nodo_origen) * 1000.0;

        // Medir Dijkstra Heap (Lista) en milisegundos (ms)
        double time_heap_disp = medir_tiempo_ejecucion(dijkstraHeap, gListaDisperso, nodo_origen) * 1000.0;

        // Guardar directo en el archivo CSV
        archivo << V << "," << E_disp << ",Disperso," << time_lineal_disp << "," << time_heap_disp << "\n";

        // =====================================================================
        // --- EVALUACIÓN EN GRAFO DENSO (|E| ≈ |V|^2 / 4) ---
        // =====================================================================
        GrafoLista gListaDenso = generarGrafo(V, true);
        GrafoMatriz gMatrizDenso = convertirAMatriz(gListaDenso);
        long long E_den = gListaDenso.todasLasAristas.size();

        // Medir Dijkstra Lineal (Matriz) en milisegundos (ms)
        double time_lineal_den = medir_tiempo_ejecucion(dijkstraLineal, gMatrizDenso, nodo_origen) * 1000.0;

        // Medir Dijkstra Heap (Lista) en milisegundos (ms)
        double time_heap_den = medir_tiempo_ejecucion(dijkstraHeap, gListaDenso, nodo_origen) * 1000.0;

        // Guardar directo en el archivo CSV
        archivo << V << "," << E_den << ",Denso," << time_lineal_den << "," << time_heap_den << "\n";
    }

    archivo.close();
    std::cout << "¡Listo! Datos guardados exitosamente en 'dijkstra_tiempos.csv'.\n";
}

int main() {
    ejecutarExperimentoDijkstra();
    return 0;
}
