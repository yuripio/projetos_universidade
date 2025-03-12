import networkx as nx
import matplotlib.pyplot as plt
from collections import deque
import pandas as pd


# Criação do grafo com cidades e pesos
def criar_grafo():
    G = nx.Graph()
    arq = pd.read_csv('distancias.csv')
    for index, row in arq.iterrows():
        origem = row['MUNICÍPIO ORIGEM']
        destino = row['MUNICÍPIO DESTINO']
        distancia = row['DISTÂNCIA TOTAL (km)']
        G.add_edge(origem, destino, weight=distancia)
    return G

# Busca em largura (BFS) para encontrar todos os caminhos possíveis (com pesos)


def bfs_todos_caminhos(G, inicio, objetivo):
    if inicio not in G or objetivo not in G:
        raise ValueError("Cidade inicial ou cidade final não estão no grafo")

    caminhos = []
    # (nó atual, caminho, distância acumulada)
    fila = deque([(inicio, [inicio], 0)])
    visitados = set()

    while fila:
        no_atual, caminho, distancia_atual = fila.popleft()

        if no_atual == objetivo:
            caminhos.append((caminho, distancia_atual))
            continue  # Continue para explorar outros caminhos

        for vizinho in G.neighbors(no_atual):
            if vizinho not in caminho:  # Verifica se o vizinho já está no caminho atual
                peso_aresta = G[no_atual][vizinho]['weight']
                fila.append(
                    (vizinho, caminho + [vizinho], distancia_atual + peso_aresta))

    return caminhos

# Função para verificar se existe um caminho entre duas cidades


def existe_caminho(G, inicio, objetivo):
    caminhos = bfs_todos_caminhos(G, inicio, objetivo)
    return len(caminhos) > 0


# Exemplo de uso
G = criar_grafo()


cidade_inicio = input("Digite a cidade de inicio do percurso: ")
print('\n')
cidade_objetivo = input("Digite a cidade de destino do percurso: ")
print('\n')

# Encontrar todos os caminhos
caminhos = bfs_todos_caminhos(G, cidade_inicio, cidade_objetivo)
if caminhos:
    print(f"Todos os caminhos de {cidade_inicio} a {cidade_objetivo}:")
    for caminho, distancia in caminhos:
        print(f"Caminho: {' -> '.join(caminho)}, Distância: {distancia} km")
else:
    print(f"Não existe caminho de {cidade_inicio} a {cidade_objetivo}")

# Verificar se existe um caminho
existe = existe_caminho(G, cidade_inicio, cidade_objetivo)
print(f"Existe um caminho de {cidade_inicio} a {cidade_objetivo}: {existe}")
