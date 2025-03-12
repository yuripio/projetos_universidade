#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED

typedef struct info Info;
typedef struct dados Dados;
typedef struct No *Apontador;
typedef struct No No;
typedef Apontador TipoDicionario;
typedef struct NO* ArvAVL;

void inserirMusica(int op, Dados *vetMain, int *tam);
int buscarNoVetor(Dados *vet, int n, char *elem);
int buscaBinaria(Dados *vet, int n, char *chave);
void shellsort(Dados *vet, int n);
void Inicializa(Apontador *Dicionario);
int Vazio(Apontador *Dicionario);
Dados* PesquisaArvBin(char *x, Apontador *p);
void InsereArvBin(Dados x, Apontador *p);
void Central(Apontador p);
ArvAVL* cria_ArvAVL();
void RotacaoLL(ArvAVL *A);
void RotacaoRR(ArvAVL *A);
void RotacaoLR(ArvAVL *A);
void RotacaoRL(ArvAVL *A);
int maior(int x, int y);
int insere_ArvAVL(ArvAVL *raiz, Dados valor);
void emOrdem_ArvAVL(ArvAVL *raiz);
int altura_NO(struct NO* no);
int fatorBalanceamento_NO(struct NO* no);
Dados* consulta_ArvAVL(ArvAVL *raiz, char *valor);
Dados* consulta_ArvAVL_Freq(ArvAVL *raiz, int valor);

#endif // PROJETO_H_INCLUDED
