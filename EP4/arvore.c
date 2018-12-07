#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"

void imprimeArvore(node raiz) {
    if (raiz != NULL) {
        imprimeArvore (raiz->esq);
        printf ("%s %d\n", raiz->info, raiz->ocorrencias);
        imprimeArvore (raiz->dir); 
   }
}

void desaloca(node raiz){
    if(raiz != NULL){
        desaloca(raiz->esq);
        desaloca(raiz->dir);
        free(raiz);
    }
}

node buscaArvore(node raiz, String x){
    if (raiz == NULL || strcmp(raiz->info, x.texto) == 0){
        if (raiz != NULL){
            raiz->ocorrencias++;
        }
        return raiz;
    }
    if (strcmp(raiz->info, x.texto) > 0)
        return buscaArvore(raiz->esq, x);
    else if (strcmp(raiz->info, x.texto) < 0)
        return buscaArvore(raiz->dir, x);
    return NULL;

}

node insereArvA(node raiz, String x) {
    node p, q, novo, jaTem;
    p = raiz; q = NULL;

    jaTem = buscaArvore(raiz, x);
    if(jaTem != NULL) return raiz;

    while (p != NULL) {     
        q = p;
        if (strcmp(p->info, x.texto) > 0){
            p = p->esq;
        }
        else if (strcmp(p->info, x.texto) < 0){
            p = p->dir;
        }
        else{
            break;
        }
    }

    if (p == NULL) {
        novo = malloc(sizeof(arvore));
        novo->info = x.texto;
        novo->ocorrencias = x.ocorrencias;
        novo->esq = novo->dir = NULL;
        novo->pai = q;
        if (q == NULL){
            // printf("erro\n\n");
            raiz = novo;
        }
        else if (strcmp(q->info, x.texto) < 0)
            q->dir = novo;
        else if (strcmp(q->info, x.texto) > 0)
            q->esq = novo;
    }
    return raiz;
}
void insereArvO(node raiz, Vet* vetor) {
    if (raiz != NULL) {
        insereArvO(raiz->esq, vetor);
        vetor->vet[vetor->index].texto = raiz->info;
        vetor->vet[vetor->index].ocorrencias = raiz->ocorrencias;
        vetor->index++;
        vetor->tamanho++;
        insereArvO(raiz->dir, vetor); 
   }
}

void criaArv(String* vetor, int numPalavras, int ordem){
    int i;
    node raiz = NULL;
    
    for(i = 0; i < numPalavras; i++){
        raiz = insereArvA(raiz, vetor[i]);
    }

    if (ordem == 1){
        imprimeArvore(raiz);
    }
    if (ordem == 2){
        Vet VetorO;
        VetorO.index = 0;
        VetorO.tamanho = 0;
        VetorO.vet = malloc(numPalavras*sizeof(String));
        insereArvO(raiz, &VetorO);
        qsort(VetorO.vet, 10, sizeof(String), comparaO);
        imprimeVetorDesordO(VetorO.vet, VetorO.tamanho);
    }
    
    desaloca(raiz);
}