#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"

void imprimeListaOrd(apontador inicio){
    apontador p;

    for(p = inicio; p != NULL; p = p->prox){
        printf("%s %d\n", p->info.texto, p->info.ocorrencias);
    }
}

apontador insereListaO(String x, apontador inicio){
    apontador atual = inicio;
    apontador novo;
    apontador ant;

    if (atual == NULL){
        novo = malloc(sizeof(apontador));
        novo->info = x;
        novo->prox = NULL;
        return novo;
    }

    apontador aux = buscaLista(x, inicio);
    if (aux != NULL){
        aux->info.ocorrencias++;
        return inicio;
    }
    
    ant = inicio;
    atual = inicio->prox;
    
    if(x.ocorrencias > ant->info.ocorrencias){
        novo = malloc(sizeof(apontador));
        novo->info = x;
        novo->prox = ant;
        ant->prox = atual;
        return novo;
    }

    while(atual != NULL && x.ocorrencias < atual->info.ocorrencias){
        ant = atual; 
        atual = atual->prox;
    }
        novo = malloc(sizeof(apontador));
        novo->info = x;
        novo->prox = atual;
        ant->prox = novo;
    return inicio;
}

apontador insereListaA(String x, apontador inicio){
    apontador atual = inicio;
    apontador novo;
    apontador ant;
    
    if (atual == NULL){
        novo = malloc(sizeof(apontador));
        novo->info = x;
        novo->prox = NULL;
        return novo;
    }

    apontador aux = buscaLista(x, inicio);
    if (aux != NULL){
        aux->info.ocorrencias++;
        return inicio;
    }
    
    ant = inicio;
    atual = inicio->prox;
    
    if(strcmp(x.texto, ant->info.texto) < 0){
        novo = malloc(sizeof(apontador));
        novo->info = x;
        novo->prox = ant;
        ant->prox = atual;
        return novo;
    }

    while(atual != NULL && strcmp(x.texto, atual->info.texto) > 0){
        ant = atual; 
        atual = atual->prox;
    }
        novo = malloc(sizeof(apontador));
        novo->info = x;
        novo->prox = atual;
        ant->prox = novo;
    return inicio;
}

void criaListaOrd(String* vetor, int tamanho, int ordem){
    int i;
    apontador inicio;
    inicio = malloc(sizeof(apontador));    
    inicio = NULL;

    for(i = 0; i < tamanho; i++){
        if (ordem == 1)
            inicio = insereListaA(vetor[i], inicio);
        if (ordem == 2)
            inicio = insereListaO(vetor[i], inicio);
    }

    imprimeListaOrd(inicio);
    free(inicio);
}