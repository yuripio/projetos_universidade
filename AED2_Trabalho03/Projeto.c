#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct No *Apontador;
typedef struct No {
    Dados Reg;
    Apontador Esq, Dir;
}No;

typedef Apontador TipoDicionario;


struct NO{
    Dados info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* ArvAVL;

void inserirMusica(int op, Dados *vet, int *tam){
    FILE *file;
    char filename[100];
    char **words = NULL;
    char word[100];
    int wordCount = 0;
    char n[100], c[50];
    switch(op){
    case 1:
            file = fopen("1.txt" , "r");
            strcpy(n, "Lanca Perfume");
            strcpy(c, "Rita Lee");
            break;
        case 2:
            file = fopen("2.txt" , "r");
            strcpy(n, "Ovelha Negra");
            strcpy(c, "Rita Lee");
            break;
        case 3:
            file = fopen("3.txt" , "r");
            strcpy(n, "Brasil");
            strcpy(c, "Cazuza");
            break;
        case 4:
            file = fopen("4.txt" , "r");
            strcpy(n, "Todo o Amor Que Houver Nessa Vida");
            strcpy(c, "Cazuza");
            break;
        case 5:
            file = fopen("5.txt" , "r");
            strcpy(n, "Todo o Amor Que Houver Nessa Vida");
            strcpy(c, "Nando Reis");
            break;
        case 6:
            file = fopen("6.txt" , "r");
            strcpy(n, "All Star");
            strcpy(c, "Nando Reis");
            break;
        case 7:
            file = fopen("7.txt" , "r");
            strcpy(n, "A Sua");
            strcpy(c, "Marisa Monte");
            break;
        case 8:
            file = fopen("8.txt" , "r");
            strcpy(n, "Velha Infância");
            strcpy(c, "Marisa Monte");
            break;
        case 9:
            file = fopen("9.txt" , "r");
            strcpy(n, "Epitafio");
            strcpy(c, "Titans");
            break;
        case 10:
            file = fopen("10.txt" , "r");
            strcpy(n, "Televisao");
            strcpy(c, "Titans");
            break;
        case 11:
            file = fopen("11.txt" , "r");
            strcpy(n, "Sutilmente");
            strcpy(c, "Skank");
            break;
        case 12:
            file = fopen("12.txt" , "r");
            strcpy(n, "Vou Deixar");
            strcpy(c, "Skank");
            break;
        case 13:
            file = fopen("13.txt" , "r");
            strcpy(n, "Eduardo e Mônica");
            strcpy(c, "Legião Urbana");
            break;
        case 14:
            file = fopen("14.txt" , "r");
            strcpy(n, "Faroeste Caboclo");
            strcpy(c, "Legião Urbana");
            break;
        case 15:
            file = fopen("15.txt" , "r");
            strcpy(n, "Maria, Maria");
            strcpy(c, "Milton Nascimento");
            break;
        case 16:
            file = fopen("16.txt" , "r");
            strcpy(n, "Quem Sabe Isso Quer Dizer Amor");
            strcpy(c, "Milton Nascimento");
            break;
        }
    if (file == NULL) {
        printf("Failed to open the file.\n");
    }

    while (fscanf(file, "%99s", word) == 1) {
        words = realloc(words, (wordCount + 1) * sizeof(char *));
        for(int i = 0; i < strlen(word); i++){
            if(word[i] >= 65 && word[i] <= 90)
                word[i] += 32;
            if(word[i] == 44)
                word[i] = '\0';
        }
        words[wordCount] = strdup(word);
        wordCount++;
    }
    fclose(file);

    Dados vetTemp[wordCount];
    int numTemp = 0;

    for(int i = 0; i < wordCount; i++){
        if(strlen(words[i]) > 3){
            int x = buscarNoVetor(vetTemp, numTemp, words[i]);
            if(x > -1){
                vetTemp[x].inform.freq++;
            }
            else{
                strcpy(vetTemp[numTemp].palavra, words[i]);
                strcpy(vetTemp[numTemp].inform.comp, c);
                strcpy(vetTemp[numTemp].inform.nome, n);
                vetTemp[numTemp].inform.freq = 1;
                numTemp++;
            }
        }
    }
    for (int i = 0; i < numTemp; i++) {
        free(words[i]);
    }
    free(words);

    for(int i = 0; i < numTemp; i++){
        int x = buscarNoVetor(vet, *tam, vetTemp[i].palavra);
        if(x > -1){
            if(vet[x].inform.freq < vetTemp[i].inform.freq){
                vet[x].inform.freq = vetTemp[i].inform.freq;
                strcpy(vet[x].inform.comp, vetTemp[i].inform.comp);
                strcpy(vet[x].inform.nome, vetTemp[i].inform.nome);
            }
            vet[x].quant += vetTemp[i].inform.freq;
        }
        else{
            strcpy(vet[*tam].palavra, vetTemp[i].palavra);
            vet[*tam].inform.freq = vetTemp[i].inform.freq;
            strcpy(vet[*tam].inform.comp, vetTemp[i].inform.comp);
            strcpy(vet[*tam].inform.nome, vetTemp[i].inform.nome);
            vet[*tam].quant = vetTemp[i].inform.freq;
            (*tam)++;
        }
    }
}

int buscarNoVetor(Dados *vet, int n, char *elem){
    int i;
    for(i = 0; i < n; i++){
        if(strcmp(elem,vet[i].palavra)==0)
            return i;
    }
    return -1;
}

int buscaBinaria(Dados *vet, int n, char *chave){
    int inf = 0, sup = n-1, meio;
    while(inf <= sup){
        meio = (inf+sup)/2;
        if(strcmp(vet[meio].palavra, chave) == 0 )
            return meio;
        else if(strcmp(vet[meio].palavra, chave) == 1)
            sup = meio - 1;
        else
            inf = meio + 1;
    }
    return -1;
}

void shellsort(Dados *vet, int n){
    int i, j;
    Dados valor;
    int interv = 1;
    do{interv = 3*interv+1;}while(interv < n);
    do{
       interv /= 3;
       for(i = interv; i < n; i++){
        valor = vet[i];
        j = i - interv;
        while(j >= 0 && (strcmp(valor.palavra, vet[j].palavra) < 0)){
          vet[j+interv] = vet[j];
          j -= interv;
        }
        vet[j+interv] = valor;
       }
    }while(interv > 1);
}

 void Inicializa(Apontador *Dicionario){
      *Dicionario = NULL;
 }

 int Vazio(Apontador *Dicionario){
      return (Dicionario == NULL);
 }

Dados* PesquisaArvBin(char *x, Apontador *p){
	if (*p == NULL){
        printf("Erro: Registro nao esta na arvore \n");
        return;
	}
	if(strcmp(x, (*p)->Reg.palavra) == -1){
        PesquisaArvBin(x, &(*p)->Esq);
        return ;
	}
	if(strcmp(x, (*p)->Reg.palavra) == 1)
        PesquisaArvBin(x, &(*p)->Dir);
	else
        return &((*p)->Reg);
}

void InsereArvBin(Dados x, Apontador *p){
	if (*p == NULL){
        *p = (Apontador)malloc(sizeof(No));
        strcpy((*p)->Reg.palavra, x.palavra);
        strcpy((*p)->Reg.inform.nome, x.inform.nome);
        strcpy((*p)->Reg.inform.comp, x.inform.comp);
        (*p)->Reg.inform.freq = x.inform.freq;
        (*p)->Reg.quant = x.quant;
        (*p)->Esq = NULL;
        (*p)->Dir = NULL;
        return;
	}
	if (strcmp(x.palavra, (*p)->Reg.palavra) == -1){
        InsereArvBin(x, &(*p)->Esq);
        return;
	}
	if (strcmp(x.palavra, (*p)->Reg.palavra) == 1)
        InsereArvBin(x, &(*p)->Dir);
    else printf("Erro: Registro ja existe na arvore \n");
}

void Central(Apontador p){
    if (p == NULL) return;
    Central (p->Esq);
    printf ("%s\n", p->Reg.palavra);
    Central (p->Dir);
}

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void RotacaoLL(ArvAVL *A){
    //printf("RotacaoLL\n");
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){
    //printf("RotacaoRR\n");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, Dados valor){
    int res;
    if(*raiz == NULL){
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;
        strcpy(novo->info.palavra, valor.palavra);
        strcpy(novo->info.inform.nome, valor.inform.nome);
        strcpy(novo->info.inform.comp, valor.inform.comp);
        novo->info.inform.freq = valor.inform.freq;
        novo->info.quant = valor.quant;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(strcmp(valor.palavra, atual->info.palavra) == -1){
        if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(strcmp(valor.palavra, (*raiz)->esq->info.palavra) == -1 ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(strcmp(valor.palavra, atual->info.palavra) == 1){
            if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if(strcmp((*raiz)->esq->info.palavra, valor.palavra) == -1){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->info);
        printf("No %s: H(%d)\n",(*raiz)->info.palavra,altura_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return (altura_NO(no->esq) - altura_NO(no->dir));
}

Dados* consulta_ArvAVL(ArvAVL *raiz, char *valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(strcmp(valor, atual->info.palavra) == 0){
            return &(atual->info);
        }
        if(strcmp(valor, atual->info.palavra) == 1)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return;
}

Dados* consulta_ArvAVL_Freq(ArvAVL *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    if(*raiz != NULL){
    if(valor ==  atual->info.quant){
        return &(atual->info);
    }
    consulta_ArvAVL_Freq(&((*raiz)->dir), valor);
    consulta_ArvAVL_Freq(&((*raiz)->esq), valor);
    }
    return;
}
