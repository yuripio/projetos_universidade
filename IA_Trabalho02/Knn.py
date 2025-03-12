import pandas as pd
from sklearn.preprocessing import normalize, LabelEncoder
import numpy as np
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
def distance(element, x):
    dist = 0
    for i in range(len(element)):
        dist += (element[i] - x[i]) ** 2
    return np.sqrt(dist)
def nearestelement(element, xtreino, ytreino, yverification):
    min_dist = float('inf')
    nearestclass = 0
    idx = 0

    for i in range(np.shape(xtreino)[0]):
        dist_atual = distance(element, xtreino[i])
        if dist_atual < min_dist and yverification[i]:
            min_dist = dist_atual
            nearestclass = ytreino[i]
            idx = i

    yverification[idx] = False
    return nearestclass, yverification
def most_common(nearest):
    return max(set(nearest), key=nearest.count)

def main():
    dados = pd.read_csv('olive.csv')
    xtreino, xteste = train_test_split(dados, test_size=0.2, random_state=32, shuffle=True)

    ytreino = list(xtreino['region'])
    yteste = list(xteste['region'])

    del xtreino['region']
    del xteste['region']

    xtreino = normalize(xtreino, axis=0)
    xteste = normalize(xteste, axis=0)

    # Gráfico do cotovelo
    k_values = list(range(1, 52, 2))  # Valores ímpares de k de 1 a 51
    acuracias = []

    for k in k_values:
        acertos = 0
        for i in range(np.shape(xteste)[0]):
            nearest = [0] * k
            yverification = [True] * len(ytreino)

            for j in range(k):
                nearest[j], yverification = nearestelement(xteste[i], xtreino, ytreino, yverification)

            if most_common(nearest) == yteste[i]:
                acertos += 1

        accuracy = acertos / np.shape(yteste)[0]
        acuracias.append(accuracy)

    # Plotando o gráfico
    plt.figure(figsize=(10, 6))
    plt.plot(k_values, acuracias, marker='o', linestyle='-', color='magenta')
    plt.title('Gráfico do Cotovelo')
    plt.xlabel('Valor de k')
    plt.ylabel('Acurácia')
    plt.grid(True)
    plt.show()

    # k = 3 para o gráfico de dispersão
    k = 3
    predictions = []

    for i in range(np.shape(xteste)[0]):
        nearest = [0] * k
        yverification = [True] * len(ytreino)

        for j in range(k):
            nearest[j], yverification = nearestelement(xteste[i], xtreino, ytreino, yverification)

        predictions.append(most_common(nearest))

    xteste_df = pd.DataFrame(xteste, columns=dados.columns[:-1])

    # Convertendo as classes categóricas para numéricas
    label_encoder = LabelEncoder()
    predictions_encoded = label_encoder.fit_transform(predictions)

    # Selecionar features
    feature1 = xteste_df.columns[3]
    feature2 = xteste_df.columns[7]

    # Criando o gráfico
    plt.figure(figsize=(10, 6))
    scatter = plt.scatter(xteste_df[feature1], xteste_df[feature2], c=predictions_encoded, cmap='viridis', s=50, edgecolor='k')
    plt.title(f'Dispersão das Previsões KNN')
    plt.xlabel(feature1)
    plt.ylabel(feature2)
    plt.colorbar(scatter, label='Classes Previstos (Codificados)')
    plt.grid(True)
    plt.show()

main()

