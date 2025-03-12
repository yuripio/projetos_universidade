import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import LabelEncoder

dados = pd.read_csv('olive.csv')
xtreino, xteste = train_test_split(dados, test_size=0.2, random_state=32, shuffle=True)

ytreino = xtreino['region'].values
yteste = xteste['region'].values

xtreino = xtreino.drop(columns=['region'])
xteste = xteste.drop(columns=['region'])

# Gráfico do cotovelo
ks = list(range(1, 52, 2))
acuracias = []

for k in ks:
    knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(xtreino, ytreino)
    y_pred = knn.predict(xteste)
    accuracy = accuracy_score(yteste, y_pred)
    acuracias.append(accuracy)

# Plotar o gráfico
plt.figure(figsize=(8, 6))
plt.plot(ks, acuracias, marker='o', linestyle='-', color='magenta')
plt.title('Gráfico do Cotovelo')
plt.xlabel('k (número de vizinhos)')
plt.ylabel('Acurácia')
plt.xticks(ks)
plt.grid(True)
plt.show()

# k = 3 para o gráfico de dispersão
knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(xtreino, ytreino)
y_pred = knn.predict(xteste)

# Selecionar features
feature1 = xteste.columns[3]
feature2 = xteste.columns[7]

# Convertendo as classes categóricas para numéricas
label_encoder = LabelEncoder()
y_pred_encoded = label_encoder.fit_transform(y_pred)

# Criar o gráfico
plt.figure(figsize=(10, 6))
scatter = plt.scatter(xteste[feature1], xteste[feature2], c=y_pred_encoded, cmap='viridis', s=50, edgecolor='k')
plt.title('Dispersão das Previsões KNN')
plt.xlabel(feature1)
plt.ylabel(feature2)
plt.colorbar(scatter, label='Classes Previstos (Codificados)')
plt.grid(True)
plt.show()
