import csv
import matplotlib.pyplot as plt

# Listas para almacenar los datos de Dijkstra
v_disperso, e_disperso, t_lineal_disp, t_heap_disp = [], [], [], []
v_denso, e_denso, t_lineal_den, t_heap_den = [], [], [], []

try:
    with open('dijkstra_tiempos.csv', mode='r', encoding='utf-8') as f:
        lector = csv.reader(f)
        next(lector)  # Omitir cabecera
        for fila in lector:
            if fila:
                vertices = int(fila[0])
                aristas = int(fila[1])
                tipo = fila[2]
                t_lineal = float(fila[3])
                t_heap = float(fila[4])
                
                if tipo == "Disperso":
                    v_disperso.append(vertices)
                    e_disperso.append(aristas)
                    t_lineal_disp.append(t_lineal)
                    t_heap_disp.append(t_heap)
                elif tipo == "Denso":
                    v_denso.append(vertices)
                    e_denso.append(aristas)
                    t_lineal_den.append(t_lineal)
                    t_heap_den.append(t_heap)
except FileNotFoundError:
    print("ERROR: No se encontró 'dijkstra_tiempos.csv'. Ejecuta primero el programa en C++.")
    exit()

# CONFIGURAR LIENZO DE DOS SUBGRÁFICAS
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6), dpi=100)
plt.style.use('seaborn-v0_8-whitegrid' if 'seaborn-v0_8-whitegrid' in plt.style.available else 'default')

# ---------------------------------------------------------------------
# PANEL 1: DIJKSTRA EN GRAFOS DISPERSOS (|E| ≈ 2|V|)
# ---------------------------------------------------------------------
ax1.plot(v_disperso, t_lineal_disp, label='Matriz + Arreglo lineal', color='#d62728', marker='o', linewidth=2)
ax1.plot(v_disperso, t_heap_disp, label='Lista + Min-Heap', color='#2ca02c', marker='s', linewidth=2)
ax1.set_title('A. Caminos cortos en grafos dispersos ($|E| \\approx 2|V|$)', fontsize=12, fontweight='bold', pad=10)
ax1.set_xlabel('Vértices ($|V|$)', fontsize=11)
ax1.set_ylabel('Tiempo de ejecución (milisegundos)', fontsize=11)
ax1.xaxis.set_major_formatter(plt.FuncFormatter(lambda x, p: format(int(x), ',')))
ax1.legend(fontsize=10, loc='upper left', frameon=True, shadow=True)
ax1.grid(True, linestyle='--', alpha=0.6)

# ---------------------------------------------------------------------
# PANEL 2: DIJKSTRA EN GRAFOS DENSOS (|E| ≈ |V|^2 / 4)
# ---------------------------------------------------------------------
ax2.plot(v_denso, t_lineal_den, label='Matriz + arreglo lineal', color='#d62728', marker='o', linewidth=2)
ax2.plot(v_denso, t_heap_den, label='Lista + Min-Heap', color='#2ca02c', marker='s', linewidth=2)
ax2.set_title('B. Caminos cortos en grafos densos ($|E| \\approx |V|^2 / 4$)', fontsize=12, fontweight='bold', pad=10)
ax2.set_xlabel('Vértices ($|V|$)', fontsize=11)
ax2.set_ylabel('Tiempo de ejecución (milisegundos)', fontsize=11)
ax2.xaxis.set_major_formatter(plt.FuncFormatter(lambda x, p: format(int(x), ',')))
ax2.legend(fontsize=10, loc='upper left', frameon=True, shadow=True)
ax2.grid(True, linestyle='--', alpha=0.6)

plt.suptitle('Análisis empírico de Dijkstra: Matriz/Lineal vs. Lista/Heap', fontsize=14, fontweight='bold', y=0.98)
plt.tight_layout()

# Guardar la gráfica
plt.savefig('grafica_complejidad_dijkstra.png', bbox_inches='tight')
print("¡Éxito! Gráfica guardada como 'grafica_complejidad_dijkstra.png'.")
plt.show()
