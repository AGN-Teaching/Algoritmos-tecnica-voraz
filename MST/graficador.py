import csv
import matplotlib.pyplot as plt

# Listas para almacenar los datos divididos por tipo de densidad
v_disperso, e_disperso, t_prim_disp, t_krus_disp = [], [], [], []
v_denso, e_denso, t_prim_den, t_krus_den = [], [], [], []

try:
    with open('mst_tiempos.csv', mode='r', encoding='utf-8') as f:
        lector = csv.reader(f)
        next(lector)  # Omitir cabecera
        for fila in lector:
            if fila:
                vertices = int(fila[0])
                aristas = int(fila[1])
                tipo = fila[2]
                t_prim = float(fila[3])
                t_krus = float(fila[4])
                
                if tipo == "Disperso":
                    v_disperso.append(vertices)
                    e_disperso.append(aristas)
                    t_prim_disp.append(t_prim)
                    t_krus_disp.append(t_krus)
                elif tipo == "Denso":
                    v_denso.append(vertices)
                    e_denso.append(aristas)
                    t_prim_den.append(t_prim)
                    t_krus_den.append(t_krus)
except FileNotFoundError:
    print("ERROR: No se encontró 'mst_tiempos.csv'. Ejecuta primero el programa en C++.")
    exit()

# CONFIGURAR LIENZO DE DOS SUBGRÁFICAS (Lado a Lado)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6), dpi=100)
plt.style.use('seaborn-v0_8-whitegrid' if 'seaborn-v0_8-whitegrid' in plt.style.available else 'default')

# ---------------------------------------------------------------------
# PANEL 1: GRAFOS DISPERSOS (|E| ≈ 2|V|)
# ---------------------------------------------------------------------
ax1.plot(v_disperso, t_prim_disp, label='Prim (Min-Heap)', color='#ff7f0e', marker='o', linewidth=2)
ax1.plot(v_disperso, t_krus_disp, label='Kruskal (Union-Find)', color='#1f77b4', marker='s', linewidth=2)
ax1.set_title('A. Rendimiento en grafos dispersos ($|E| \\approx 2|V|$)', fontsize=12, fontweight='bold', pad=10)
ax1.set_xlabel('Vértices ($|V|$)', fontsize=11)
ax1.set_ylabel('Tiempo de ejecución (milisegundos)', fontsize=11)
ax1.xaxis.set_major_formatter(plt.FuncFormatter(lambda x, p: format(int(x), ',')))
ax1.legend(fontsize=10, loc='upper left', frameon=True, shadow=True)
ax1.grid(True, linestyle='--', alpha=0.6)

# ---------------------------------------------------------------------
# PANEL 2: GRAFOS DENSOS (|E| ≈ |V|^2 / 4)
# ---------------------------------------------------------------------
ax2.plot(v_denso, t_prim_den, label='Prim (Min-Heap)', color='#ff7f0e', marker='o', linewidth=2)
ax2.plot(v_denso, t_krus_den, label='Kruskal (Union-Find)', color='#1f77b4', marker='s', linewidth=2)
ax2.set_title('B. Rendimiento en grafos densos ($|E| \\approx |V|^2 / 4$)', fontsize=12, fontweight='bold', pad=10)
ax2.set_xlabel('Vértices ($|V|$)', fontsize=11)
ax2.set_ylabel('Tiempo de ejecución (milisegundos)', fontsize=11)
ax2.xaxis.set_major_formatter(plt.FuncFormatter(lambda x, p: format(int(x), ',')))
ax2.legend(fontsize=10, loc='upper left', frameon=True, shadow=True)
ax2.grid(True, linestyle='--', alpha=0.6)

# Ajustes generales del reporte visual
plt.suptitle('Análisis empírico de algoritmos MST: Prim vs. Kruskal', fontsize=14, fontweight='bold', y=0.98)
plt.tight_layout()

# Guardar la gráfica combinada
plt.savefig('grafica_complejidad_mst.png', bbox_inches='tight')
print("¡Éxito! Gráfica guardada como 'grafica_complejidad_mst.png'.")
plt.show()
