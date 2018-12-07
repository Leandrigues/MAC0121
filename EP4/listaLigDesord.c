#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"

void imprimeListaDesord(apontador inicio, int tamanho, int ordem){
    apontador atual;
    int i = 0;
    String* vetor = malloc(sizeof(String)*tamanho);

    for(atual = inicio; atual != NULL; atual = atual->prox){
        vetor[i] = atual->info;
        i++;
    }
    
    if (ordem == 1){
        qsort(vetor, tamanho, sizeof(String), comparaA);    
    }

    if (ordem == 2){
        qsort(vetor, tamanho, sizeof(String), comparaO);    
    }

    imprimeVetorOrd(vetor, tamanho);
}

apontador buscaLista(String x, apontador inicio){
    /* Função de busca utilizada nas duas implementações de lista */
    apontador atual = inicio;

    while(atual != NULL && strcmp(atual->info.texto, x.texto) != 0){
        atual = atual->prox;
    }
    if(atual != NULL){
        return atual;
    }
    return NULL;
}

apontador insereListaDesord(String x, apontador inicio){
    apontador aux = buscaLista(x, inicio);

    if (aux == NULL){
        apontador novo = malloc(sizeof(apontador));
        novo->prox = inicio;
        novo->info = x;
        return novo;
    }

    else{
        aux->info.ocorrencias++;
        return inicio;
    }
}


 void criaListaDesord(String* vetor, int tamanho, int ordem){
    int i;
    apontador inicio;  
    inicio = malloc(sizeof(apontador));
    inicio = NULL;

    for(i = 0; i < tamanho; i++){
        inicio = insereListaDesord(vetor[i], inicio);
    }

    imprimeListaDesord(inicio, tamanho, ordem);
    free(inicio);
}