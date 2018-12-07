#ifndef __ESTRUTURAS_H__
#define __ESTRUTURAS_H__

/* Struct para armazenamento de palavras */
typedef struct palavra {
    char* texto;
    int ocorrencias;
} String;

/* Struct os nós da ABB */
typedef struct arvore {
  char* info;
  int ocorrencias;
  struct arvore* pai;
  struct arvore* esq;
  struct arvore* dir;
} arvore;

typedef struct vetor {
  String* vet;
  int tamanho;
  int index;
} Vet;

typedef struct tupla {
  int pos;
  int flag;
} tupla;

/* Struct de celula de lista ligada */
struct celula {
  String info;
  struct celula *prox;
};

typedef struct celula *apontador;
typedef arvore* node;

/* Declaração das funções globais */
int comparaA(const void *a, const void *b);
int comparaO(const void *a, const void *b);

/* Declração das funções de vetor desordenado */
int buscaVetorDesord(String* vetor, char* palavra, int tamanho);
int insereVetorDesord(String* vetorDesord, char* palavra, int index);
void imprimeVetorDesordO(String* vetor, int tamanho);
void imprimeTeste(String* vetor, int tamanho);
void troca(String* i, String* j);
int cmpWord(const void *a, const void *b);
void imprimeVetorDesordA(String* vetor, int tamanho);
String* resize(String* vetor, int tamanho);
Vet criaVetorDesord(String* vetorAuxiliar, int numPalavras);

/* Declsração das funções de árvore de busca binária */
void criaArv(String* vetor, int numPalavras, int ordem);
void imprimeArvore(node raiz);
node buscaArvore(node raiz, String x);
node insereArvA(node raiz, String x);
void insereArvO(node raiz, Vet* Vetor);
void desaloca(node raiz);

/*  Declaração das funções de vetor ordenado */
void criaVetorOrd(Vet vetorAux, int ordem);
void imprimeVetorOrd(String* vetor, int tamanho);
tupla buscaBinariaA(String* vetor, String x, int ini, int fim);
String* shift(String* vetor, int indice, int tamanho);
int insereA(String* vetor, String x, int tamanho);
int insereO(String* vetor, String x, int tamanho);

/*  Declaração das funções de lista ligada desordenada */
void criaListaDesord(String* vetor, int tamanho, int ordem);
void imprimeListaDesord(apontador inicio, int tamanho, int ordem);
apontador buscaLista(String x, apontador inicio);
apontador insereListaDesord(String x, apontador inicio);

/*  Declaração das funções de lista ligada ordenada */
void imprimeListaOrd(apontador inicio);
apontador insereListaO(String x, apontador inicio);
apontador insereListaA(String x, apontador inicio);
void criaListaOrd(String* vetor, int tamanho, int ordem);

#endif