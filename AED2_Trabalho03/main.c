#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Projeto.h"

typedef struct info{
    char nome[100];
    char comp[50];
    int freq;
}Info;

typedef struct dados{
    char palavra[100];
    Info inform;
    int quant;
}Dados;

int main(){
    int op, tam = 0;
    char pesq[50];
    Dados vet[5000];
    time_t ini;
    time_t fim;
    do{
        printf("Escolha uma musica para adicionar a analise da pesquisa:\n");printf("1-Lanca Perfume - Rita Lee\n");printf("2-Ovelha Negra - Rita Lee\n");printf("3-Brasil - Cazuza\n");
        printf("4-Todo o Amor Que Houver Nessa Vida - Cazuza\n");printf("5-Pra Você Guardei o Amor - Nando Reis\n");printf("6-All Star - Nando Reis\n");printf("7-A Sua - Marisa Monte\n");
        printf("8-Velha Infância - Marisa Monte\n");printf("9-Epitafio - Titans\n");printf("10-Televisao - Titans\n");printf("11-Sutilmente - Skank\n");printf("12-Vou Deixar - Skank\n");
        printf("13-Eduardo e Mônica - Legião Urbana\n");printf("14-Faroeste Caboclo - Legião Urbana\n");printf("15-Maria, Maria - Milton Nascimento\n");printf("16-Quem Sabe Isso Quer Dizer Amor - Milton Nascimento\n");
        printf("0 - TERMINAR ESCOLHAS\n");
        scanf("%d", &op);
        if(op != 0)
            inserirMusica(op, vet, &tam);
    }while(op != 0);
    shellsort(vet, tam);
    printf("Escreva a palavra usada para a pesquisa: ");
    scanf("%s", &pesq);
    printf("\n\nDados obtidos pela pesquisa binaria\n");
    ini = clock();
    int x = buscaBinaria(vet, tam , pesq);
    fim = clock();
    if(x >= 0)
        printf("A palavra %s tem %d ocorrencias, sendo a maior frequencia de %d na musica %s de %s\n", vet[x].palavra, vet[x].quant, vet[x].inform.freq, vet[x].inform.nome, vet[x].inform.comp);
    else
        printf("A palavra nao foi encontrada\n");
    printf("O tempo da busca binaria foi %f\n", ((double)(fim-ini)/CLOCKS_PER_SEC));

    printf("\n\nDados obtidos pela pesquisa em arvore binaria\n");
    ini = clock();
    TipoDicionario dic;
    Inicializa(&dic);
    for(int i = 0; i < tam; i++){
        InsereArvBin(vet[i], &dic);
    }
    fim = clock();
    printf("O tempo adicional para construcao da arvore binaria eh de: %f\n",((double)(fim-ini)/CLOCKS_PER_SEC));
    ini = clock();
    Dados *y = PesquisaArvBin(pesq, &dic);
    fim = clock();
    if(y != NULL){
        printf("A palavra %s tem %d ocorrencias, sendo a maior frequencia de %d na musica %s de %s\n", y->palavra, y->quant, y->inform.freq, y->inform.nome, y->inform.comp);
        printf("O tempo de execucao da pesquisa em arvore binaria foi de: %f\n", ((double)(fim-ini)/CLOCKS_PER_SEC));
    }
    else
        printf("A palavra nao foi encontrada\n");
    printf("\n\nDados obtidos pela pesquisa em arvore avl\n");
    ini = clock();
    ArvAVL* avl;
    avl = cria_ArvAVL();
    for(int i=0 ;i<tam ; i++){
        insere_ArvAVL(avl, vet[i]);
    }
    fim = clock();
    printf("O tempo adicional para construcao da arvore avl eh de: %f\n",((double)(fim-ini)/CLOCKS_PER_SEC));
    ini = clock();
    Dados *z = consulta_ArvAVL(avl, pesq);
    fim = clock();
    if(z != NULL){
        printf("A palavra %s tem %d ocorrencias, sendo a maior frequencia de %d na musica %s de %s\n", z->palavra, z->quant, z->inform.freq, z->inform.nome, z->inform.comp);
        printf("O tempo de execucao da pesquisa em arvore avl foi de: %f\n", ((double)(fim-ini)/CLOCKS_PER_SEC));
    }
    else
        printf("A palavra nao foi encontrada\n");
    return 0;
}
