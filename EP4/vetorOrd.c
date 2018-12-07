#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"

void imprimeVetorOrd(String* vetor, int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("%s %d\n", vetor[i].texto, vetor[i].ocorrencias);
    }
}


tupla buscaBinariaA(String* vetor, String x, int ini, int fim){
    int meio = ini + (fim-ini)/2;
    tupla Tup;

    if (fim >= ini){
        // printf("PALAVRA %s ini %d fim %d meio %d vetor[mei/o] = %s\n",x.texto,ini, fim, meio, vetor[meio].texto);
        if (strcmp(vetor[meio].texto, x.texto) == 0){
            Tup.pos = meio;
            Tup.flag = 1;
            return Tup;
        }

        if (strcmp(vetor[meio].texto, x.texto) > 0){
            // printf("%s VEM ANTES DE %s\n", x.texto, vetor[meio].texto);
            return buscaBinariaA(vetor, x, ini, meio-1);
        }

        if (strcmp(vetor[meio].texto, x.texto) < 0){
            // printf("%s VEM DEPOIS DE %s\n", x.texto, vetor[meio].texto  );
            return buscaBinariaA(vetor, x, meio+1, fim);
        }
    }

    Tup.pos = meio;
    Tup.flag = -1;
    return Tup;
}

String* shift(String* vetor, int indice, int tamanho){
    int i;

    for (i = tamanho-1; i > indice ; i--){
        vetor[i] = vetor[i-1];
    }
    return vetor;
}

int insereA(String* vetor, String x, int tamanho){
    tupla aux;

    if(tamanho == 0){
        vetor[0] = x;
        return 1;
    }
    else{
        aux = buscaBinariaA(vetor, x, 0, tamanho-1);
        if(aux.flag == 1){
            vetor[aux.pos].ocorrencias++;
            return -1;
        }
        else{
            vetor = shift(vetor, aux.pos, tamanho);
            vetor[aux.pos] = x;
            return 1;
            }
    }

}


int insereO(String* vetor, String x, int tamanho){
    int i;

    if (tamanho == 0){
        vetor[0] = x;
        return 1;
    }

    else{
        for(i = 0; i < tamanho; i++){
            if(vetor[i].texto == x.texto){
                vetor[i].ocorrencias++;
                return -1;
            }
        }
        return 1;
    }
}

void criaVetorOrd(Vet vetorAux, int ordem){
    int i, k;
    Vet Vetor;
    Vetor.vet = malloc(sizeof(String)*(1+vetorAux.tamanho));
    Vetor.tamanho = 0;

    if (ordem == 1){
        for(i = 0; i < vetorAux.tamanho; i++){
            k = insereA(Vetor.vet, vetorAux.vet[i], Vetor.tamanho);
            if(k == 1)
                Vetor.tamanho++;
        }
        imprimeVetorOrd(Vetor.vet, Vetor.tamanho);
    }

    if (ordem == 2){
        for(i = 0; i < vetorAux.tamanho; i++){
            insereO(Vetor.vet, vetorAux.vet[i], Vetor.tamanho);
            k = insereO(Vetor.vet, vetorAux.vet[i], Vetor.tamanho);
            if(k == 1){
                Vetor.tamanho++;
                Vetor.vet[i] = vetorAux.vet[i];
                qsort(Vetor.vet, Vetor.tamanho, sizeof(String), comparaO);    
            }
        }
        imprimeVetorOrd(Vetor.vet, Vetor.tamanho);
        }
}