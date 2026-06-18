# Laboratorio 4: Análisis empírico de algoritmos de técnica voraz

Este repositorio contiene la infraestructura de código base para para un ejercicio de laboratorio de **Análisis y Diseño de Algoritmos**. El objetivo de esta práctica es evaluar empíricamente cómo la elección y combinación de estructuras de datos altera drásticamente el rendimiento físico (tiempo de ejecución en hardware) de los algoritmos de **Prim**, **Kruskal** y **Dijkstra**.

La práctica se divide en dos bloques independientes de experimentación.

---

## Requisitos del entorno

Antes de comenzar, asegúrate de contar con las siguientes herramientas instaladas en tu sistema:
* **Compilador de C++** compatible con el estándar C++17 o superior (`g++` o `clang++`).
* **Python 3.x** con la biblioteca de graficación instalada:
  ```bash
  pip install matplotlib
  ```

## Estructura del repositorio
El código está modularizado para separar las estructuras de datos genéricas de la lógica de los experimentos:

`grafo.h`: Define las representaciones del grafo (GrafoLista y GrafoMatriz).

`union_find.h`: Implementación de conjuntos disjuntos optimizada con compresión de caminos.

`tiempoejecucion.h`: Módulo genérico de cronometraje de funciones de alta resolución.

`generador.h`: Generador de grafos aleatorios conexos con densidades controladas (Disperso vs. Denso).

### Bloque 1: MST (Prim vs. Kruskal)

`mst.h`: Funciones de resolución de Prim (usando std::priority_queue) y Kruskal.

`main.cpp`: Programa de control que toma tiempos de MST y genera `mst_tiempos.csv`.

`graficador.py`: Script para generar la gráfica comparativa de paneles.

### Bloque 2: Caminos cortos (Dijkstra Lineal vs. Heap)

`dijkstra.h`: Implementación de Dijkstra Lineal (Matriz) y Dijkstra con Heap (Lista).

`main.cpp`: Programa de control que toma tiempos de ruteo y genera `dijkstra_tiempos.csv`.

`graficador.py`: Script para generar la gráfica comparativa de paneles.


## Estudio experimental
Los experimentos deben compilarse y ejecutarse de forma independiente para evitar la contaminación de archivos de salida.

### Experimento 1: Árboles de expansión mínimos (MST)
1. Compilar el programa en C++:
```
g++ -std=c++17 main.cpp -o mst.o
```

2. Ejecutar las pruebas temporales:
```
./mst.o
```
Esto procesará muestras incrementales desde $|V|=1,000$ hasta $|V|=5,000$ y creará de forma automatizada el archivo `mst_tiempos.csv`.

3. Generar las curvas de crecimiento:
```
python graficador.py
```
El script mostrará en pantalla y guardará el archivo visual `grafica_complejidad_mst.png` con la comparativa en paneles dispersos y densos.

### Experimento 2: Caminos más cortos (Dijkstra)
1. Compilar el programa en C++:
```
g++ -std=c++17 main.cpp -o dijkstra.o
```

2. Ejecutar las pruebas temporales:
```
./dijkstra.o
```
El programa calculará las distancias mínimas desde un nodo origen fijo y creará de forma automatizada el archivo `dijkstra_tiempos.csv`.

3. Generar las curvas de crecimiento:
```
python graficador.py
```
El script procesará los datos y generará el archivo visual `grafica_complejidad_dijkstra.png`.
