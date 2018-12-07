#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"

int buscaVetorDesord(String* vetor, char* palavra, int tamanho){
    int i;

    for(i = 0; i < tamanho; i++){
        if(strcmp(vetor[i].texto, palavra) == 0){
            return i;
        }
    }
    return -1;
}

int insereVetorDesord(String* vetorDesord, char* palavra, int index){
    int aux = buscaVetorDesord(vetorDesord, palavra, index);

    if (aux == -1){
        vetorDesord[index].texto = malloc(sizeof(char)*strlen(palavra));
        vetorDesord[index].ocorrencias = 1;
        strcpy(vetorDesord[index].texto, palavra);
        return 1;
    }
    else{
        vetorDesord[aux].ocorrencias++;
        return 0;
    }
}

void imprimeVetorDesordO(String* vetor, int tamanho){
    int k = tamanho, i, j = tamanho;

    while(k != 0){
        for(i = 0; i < tamanho; i ++){
            if(vetor[i].ocorrencias == j){
                printf("%s %d\n", vetor[i].texto, vetor[i].ocorrencias);
                k--;
            }
        }
        j--;
    }
}
void imprimeTeste(String* vetor, int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("%s ", vetor[i].texto);
    }
}

void troca(String* i, String* j){
    String aux;

    aux = *i;
    *i = *j;
    *j = aux;
}

void imprimeVetorDesordA(String* vetor, int tamanho){
    String* vetorAux = malloc(sizeof(String)*tamanho);
    int i, aux;
    
    for(i = 0; i < tamanho; i++){
        aux = strlen(vetor[i].texto);
        vetorAux[i].texto = malloc(aux*sizeof(char));
        vetorAux[i].texto = vetor[i].texto;
        vetorAux[i].ocorrencias = vetor[i].ocorrencias;
    }
    qsort(vetorAux, tamanho, sizeof(String), comparaA);

    for(i = 0; i < tamanho; i++){
        printf("%s %d\n", vetorAux[i].texto, vetorAux[i].ocorrencias);
    }

}


String* resize(String* vetor, int tamanho){
    vetor = realloc(vetor, tamanho*2*sizeof(String));
    return vetor;    
}

Vet criaVetorDesord(String* vetorAuxiliar, int numPalavras){
    int i = 0, j = 0, aloca = 5, inserido;
    String* vetorDesord = malloc(sizeof(String)*aloca);
    Vet aux;

    while(j < numPalavras){
        inserido = insereVetorDesord(vetorDesord, vetorAuxiliar[j].texto, i);
        if(inserido) i++;
        j++;

        if (i == aloca - 1){
            vetorDesord = resize(vetorDesord, aloca);
            aloca = 2*aloca ;
        }
    }
    aux.vet = malloc(i*sizeof(String));
    aux.vet = vetorDesord;
    aux.tamanho = i;
    return aux;
}
