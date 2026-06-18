#include <iostream>
#include <fstream>
#include <vector>
#include "grafo.h"
#include "generador.h"
#include "mst.h"
#include "tiempoejecucion.h"

void ejecutarExperimentoMST() {
    // Abrir el archivo para escribir los resultados
    std::ofstream archivo("mst_tiempos.csv");
    if (!archivo.is_open()) {
        std::cerr << "ERROR: No se pudo crear el archivo mst_tiempos.csv\n";
        return;
    }

    std::cout << "Iniciando toma de tiempos para Prim y Kruskal...\n";
    
    // Escribir la cabecera del archivo CSV
    archivo << "Vertices,Aristas,Tipo,TiempoPrim,TiempoKruskal\n";

    // Tamaños de control incrementales para los grafos (|V|)
    std::vector<int> tamanos = {1000, 2000, 3000, 4000, 5000};

    for (int V : tamanos) {
        std::cout << "Procesando |V| = " << V << "..." << std::endl;

        // =====================================================================
        // --- EVALUACIÓN EN GRAFO DISPERSO ---
        // =====================================================================
        GrafoLista gDisperso = generarGrafo(V, false);
        long long E_disp = gDisperso.todasLasAristas.size();

        // Medir tiempos en milisegundos (ms)
        double time_prim_disp = medir_tiempo_ejecucion(prim, gDisperso) * 1000.0;
        double time_krus_disp = medir_tiempo_ejecucion(kruskal, gDisperso) * 1000.0;

        // Guardar directo en el archivo
        archivo << V << "," << E_disp << ",Disperso," << time_prim_disp << "," << time_krus_disp << "\n";

        // =====================================================================
        // --- EVALUACIÓN EN GRAFO DENSO ---
        // =====================================================================
        GrafoLista gDenso = generarGrafo(V, true);
        long long E_den = gDenso.todasLasAristas.size();

        // Medir tiempos en milisegundos (ms)
        double time_prim_den = medir_tiempo_ejecucion(prim, gDenso) * 1000.0;
        double time_krus_den = medir_tiempo_ejecucion(kruskal, gDenso) * 1000.0;

        // Guardar directo en el archivo
        archivo << V << "," << E_den << ",Denso," << time_prim_den << "," << time_krus_den << "\n";
    }

    archivo.close();
    std::cout << "¡Listo! Datos guardados exitosamente en 'mst_tiempos.csv'.\n";
}

int main() {
    ejecutarExperimentoMST();
    return 0;
}
