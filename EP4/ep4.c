#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"

/* Funções de comparação utilizadas no qsort() */
int comparaO(const void *a, const void *b){
    String *palavraA = (String *) a;
    String *palavraB = (String *) b;
    return (palavraA->ocorrencias < palavraB->ocorrencias);
}

int comparaA(const void *a, const void *b){
    String *palavraA = (String *) a;
    String *palavraB = (String *) b;
    return strcmp(palavraA->texto, palavraB->texto);
}

int comparaListaA(const void *a, const void *b){
    /* Função compara utilizada no quicksort para critério de desempate de palavras de lista ligada.
    A função é igual a comparaA, exceto por inverter o sinal do retorno, para que a lista não fique invertida */
    String *palavraA = (String *) a;
    String *palavraB = (String *) b;
    return (strcmp(palavraB->texto, palavraA->texto));
}

// Funções auxiliares de leitura
void removeChar(char *str, char caracter1, char caracter2, char caracter3, char caracter4, char caracter5) {
    /* Remove pontos, vigulas, etc...*/
    char *percorre, *alfanum;

    for (percorre = alfanum = str; *percorre != '\0'; percorre++) {
        *alfanum = *percorre;
        if (*alfanum != caracter1 && *alfanum != caracter2 && *alfanum != caracter3 &&\
         *alfanum != caracter4 && *alfanum != caracter5) alfanum++;
    }
    *alfanum = '\0';
}

int contaPalavras(FILE* f){
    /* Conta o número de palavras do arquivo */
    char palavra[30];
    int flag = 0, i, terminou = 0, numPalavras = 0;

    for(i = 0; !terminou; i++){
        flag = fscanf(f, "%s", palavra);
        if (flag != EOF){
            numPalavras++;
        }
        else terminou = 1;
    }

    return numPalavras;
}

void leArquivo(FILE* f, int numPalavras, int estrutura, int ordem){
    /* Faz a leitura do arquivo e armazena num vetor, além de chamar as funções de criação e impressão das estruturas */
    char palavra[30];
    int flag = 0, i = 0, terminou = 0, cont = 0;
    String* vetorAuxiliar = malloc(30*sizeof(String)*(numPalavras));
    while(!terminou){
        flag = fscanf(f, "%s", palavra);
        if (flag != EOF){
            removeChar(palavra, '.', ',', ' ', ';', '"');
            palavra[0] = tolower(palavra[0]);
            vetorAuxiliar[i].texto = malloc(sizeof(char)*strlen(palavra));
            strcpy(vetorAuxiliar[i].texto, palavra);
            i++;
        }
        else
            terminou = 1;
        cont++;
        }

    if (estrutura == 1){
        Vet vetorDesord = criaVetorDesord(vetorAuxiliar, numPalavras);
        if (ordem == 1)
            imprimeVetorDesordA(vetorDesord.vet, vetorDesord.tamanho);
        if (ordem == 2){
            qsort(vetorDesord.vet, vetorDesord.tamanho, sizeof(String), comparaA);    
            imprimeVetorDesordO(vetorDesord.vet, vetorDesord.tamanho);
        }  
        free(vetorDesord.vet);
    }

    if (estrutura == 2){
        if (ordem == 1){
            Vet vetorDesord = criaVetorDesord(vetorAuxiliar, numPalavras);
            qsort(vetorDesord.vet, vetorDesord.tamanho, sizeof(String), comparaA);    
            criaVetorOrd(vetorDesord, ordem);
            free(vetorDesord.vet);
        }
        if(ordem == 2){
            Vet vetorDesord = criaVetorDesord(vetorAuxiliar, numPalavras);
            criaVetorOrd(vetorDesord, ordem);
            free(vetorDesord.vet);
        }
    }

    if (estrutura == 3){
        Vet vetorDesord = criaVetorDesord(vetorAuxiliar, numPalavras);
        criaListaDesord(vetorDesord.vet, vetorDesord.tamanho, ordem);
        free(vetorDesord.vet);
    }

    if (estrutura == 4){
        Vet vetorDesord = criaVetorDesord(vetorAuxiliar, numPalavras);
        if(ordem == 1)
            criaListaOrd(vetorDesord.vet, vetorDesord.tamanho, ordem);
        if(ordem == 2){
            qsort(vetorDesord.vet, vetorDesord.tamanho, sizeof(String), comparaListaA);    
            criaListaOrd(vetorDesord.vet, vetorDesord.tamanho, ordem);
        }
        free(vetorDesord.vet);
    }

    if (estrutura == 5){
        Vet vetorDesord = criaVetorDesord(vetorAuxiliar, numPalavras);
        criaArv(vetorDesord.vet, vetorDesord.tamanho, ordem);
        free(vetorDesord.vet);
    }
    
    free(vetorAuxiliar);
}

int main(int argc, char** argv){
    char* arquivo = argv[1]; 
    FILE* f = fopen(arquivo, "r");
    int numPalavras = contaPalavras(f), estrutura, ordem;
    fseek(f, 0L, SEEK_SET); 

    if(strcmp(argv[3], "A") == 0)
        ordem = 1;
    if(strcmp(argv[3], "O") == 0)
        ordem = 2;
    if(strcmp(argv[3], "T") == 0)
        ordem = 3;
    if(strcmp(argv[2], "VD") == 0)
        estrutura = 1;
    if(strcmp(argv[2], "VO") == 0)
        estrutura = 2;
    if(strcmp(argv[2], "LD") == 0)
        estrutura = 3;
    if(strcmp(argv[2], "LO") == 0)
        estrutura = 4;    
    if(strcmp(argv[2], "AB") == 0)
        estrutura = 5;
        
    leArquivo(f, numPalavras, estrutura, ordem);

    return 0;
}