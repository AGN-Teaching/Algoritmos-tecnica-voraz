#ifndef TIEMPOEJECUCION_H
#define TIEMPOEJECUCION_H


#include <chrono>
#include <functional>

/**
 * Función genérica para medir el tiempo de ejecución
 */
template <typename Func, typename... Args>
double medir_tiempo_ejecucion(Func&& algoritmo, Args&&... args) {
    
    // Toma el tiempo justo antes de iniciar
    auto tiempo_inicio = std::chrono::high_resolution_clock::now();

    // Ejecutar el algoritmo con los argumentos proporcionados
    std::invoke(std::forward<Func>(algoritmo), std::forward<Args>(args)...);

    // Toma el tiempo inmediatamente después de terminar
    auto tiempo_fin = std::chrono::high_resolution_clock::now();

    // Calcular la diferencia en segundos
    // milisegundos: std::chrono::duration<double, std::milli>
    // microsegundos: std::chrono::duration<double, std::micro>
    std::chrono::duration<double> tiempo_transcurrido = tiempo_fin - tiempo_inicio;

    return tiempo_transcurrido.count();
}


#endif // TIEMPOEJECUCION_H
