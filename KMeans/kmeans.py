# Importar bibliotecas
import pandas as pd
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Carregar o dataset
data = pd.read_csv('Mall_Customers.csv')

# Converte a coluna Gender(Sexo) em valores numéricos (Male=0, Female=1)
data['Gender'] = data['Gender'].map({'Male': 0, 'Female': 1})

# Selecionar as colunas para a análise (Gender, Age, Annual Income, Spending Score)
X = data[['Gender', 'Age', 'Annual Income (k$)', 'Spending Score (1-100)']]

# Método do cotovelo para encontrar o número ideal de clusters
inertia = []
silhouette_scores = []
K = range(2, 11)  # Começa com 2 clusters pois 1 cluster não é válido para Silhouette Score
for k in K:
    kmeans = KMeans(n_clusters=k, random_state=0)
    kmeans.fit(X)
    inertia.append(kmeans.inertia_)
    silhouette_scores.append(silhouette_score(X, kmeans.labels_))

# Plotar o método do cotovelo
plt.figure(figsize=(8, 5))
plt.plot(K, inertia, 'bo-', markersize=8)
plt.xlabel('Número de Clusters (k)')
plt.ylabel('Inércia')
plt.title('Método do Cotovelo para Determinação do Número Ideal de Clusters')
plt.xticks(K)
plt.grid(True)
plt.show()

# Encontrar o número de clusters com o maior Silhouette Score
ideal_clusters = K[silhouette_scores.index(max(silhouette_scores))]

# Perguntar ao usuário quantos clusters deseja criar
num_clusters = int(input(f"Quantos clusters você deseja criar? (Sugerido: {ideal_clusters}) "))

# Aplicar K-Means com o número de clusters escolhido
kmeans = KMeans(n_clusters=num_clusters, random_state=0)
data['Cluster'] = kmeans.fit_predict(X)

# Verificar os centróides dos clusters
centroids = kmeans.cluster_centers_

# Resumo dos clusters
cluster_summary = data.groupby('Cluster').mean(numeric_only=True)[['Gender', 'Age', 'Annual Income (k$)', 'Spending Score (1-100)']]
cluster_summary['Size'] = data['Cluster'].value_counts().sort_index()
print(cluster_summary)

# Visualizar os clusters em 3D
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

#Colormap com variedade de cores para nao repetir cores na hora do plot do grafico de dispersao
colors = plt.get_cmap('tab20', num_clusters)

# Criar o gráfico 3D
for cluster in range(num_clusters):
    ax.scatter(
        data.loc[data['Cluster'] == cluster, 'Age'],
        data.loc[data['Cluster'] == cluster, 'Annual Income (k$)'],
        data.loc[data['Cluster'] == cluster, 'Spending Score (1-100)'],
        s=50, c=[colors(cluster)], label=f'Cluster {cluster}'
    )

# Marcar os centróides em 3D
ax.scatter(centroids[:, 1], centroids[:, 2], centroids[:, 3], s=200, c='yellow', marker='X', edgecolor='black', label='Centróides')

# Nomear label dos eixos
ax.set_xlabel('Idade')
ax.set_ylabel('Renda Anual (k$)')
ax.set_zlabel('Pontuação de Gastos (1-100)')
ax.set_title('Clusters de Clientes')
ax.legend()
plt.show()
