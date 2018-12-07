#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char* texto;
    int tam;
    int posX;
    int posY;
    int* horizontaisX;
    int* horizontaisY;
    int* verticaisX;
    int* verticaisY;
    int* verticais;
    int ori;
    int temPossibilidadeH;
    int temPossibilidadeV;
    int inserida;
    int possibilidadesH;
    int possibilidadesV;
    int tentativasH;
    int tentativasV;
    int tentouH;
    int tentouV;
} Palavra;


typedef struct{
    int* tamanhos;
    int* posX;
    int* posY;
    int ori;
    int tamanhoVetor;
} Livres;

typedef struct {
    Palavra* v;
    int topo;
    int max;
} pilha;

typedef pilha* Pilha;
// FUNÇÕES GERAIS
int procuraSolucao(int m, int n, int** matrizInt, Palavra* palavras, int numPalavras, Livres livresX, Livres livresY, char** matrizChar, int instancia);
void removePalavra(Palavra* atual, char** matrizChar, int m, int n, int** matrizInt);
void possiveisPos(Palavra* atual, Livres espLivre, char** matrizChar, int m, int n);
int podeInserir(char** matrizChar, Palavra* atual, int m, int n, int tentativa);
void inserePalavra(char** matrizChar, Palavra* atual, int m, int n, int tentativa, int** matrizInt);
Livres tamanhosLivresX(int ** matriz, int m, int n);
Livres tamanhosLivresY(int ** matriz, int m, int n);
void imprimeMatriz(char **matrizChar, int m, int n);
void constroiTamanhos(Palavra* atual);
// FUNÇÕES DE PILHA
void DestroiPilha(Pilha P);
void Empilha(Pilha P, Palavra el);
void resize(Pilha P);
int PilhaVazia(Pilha P);

int main(){
    int m = 1, n = 1, i, j, k, **matrizTab, numPalavras, **matrizInt, instancia = 1;
    char** matrizChar;
    Palavra* palavras;
    while (m != 0 && n != 0){   
        scanf("%d %d", &m, &n);
        if (m == 0 || n == 0) return 0;
        matrizTab = malloc(sizeof(int*)*m);
        for(i = 0; i < m; i++){
            matrizTab[i] = malloc(n*sizeof(int));
            for(j = 0; j < n; j++){
                scanf("%d", &matrizTab[i][j]);
            }

        }

        scanf("%d", &numPalavras);
        palavras = malloc(numPalavras*sizeof(Palavra));
        for (k = 0; k < numPalavras; k++){
            palavras[k].texto = malloc(100*sizeof(char));
            scanf("%s", palavras[k].texto);
        }

        matrizChar = malloc(sizeof(char*)*m);
        for(i = 0; i < m; i++){
            matrizChar[i] = malloc(n*sizeof(char)*50);
            for(j = 0; j < n; j++){
                if(matrizTab[i][j] == 0) matrizChar[i][j] = '-';
                else matrizChar[i][j] = '*';
            }
        }
        // Matriz para verificar o cruzamento de duas palavras
        matrizInt = malloc(sizeof(int)*m*50);
        for(i = 0; i < m; i++){
            matrizInt[i] = malloc(sizeof(int)*n*50);
            for(j = 0; j < n; j++){
                matrizInt[i][j] = 0;
            }
        }
        Livres livresX = tamanhosLivresX(matrizTab, m, n);
        Livres livresY = tamanhosLivresY(matrizTab, m, n);
        procuraSolucao(m, n, matrizInt, palavras, numPalavras, livresX, livresY, matrizChar, instancia);
        instancia++;
    }
        free(matrizChar);
        free(matrizInt);
        free(matrizTab);
        free(palavras);
        free(matrizInt);
}

int PilhaVazia(Pilha P) {
    if (P -> topo == 0) return 1;
    return 0;
}

void resize(Pilha P) {
    Palavra* novaPilha = malloc(2*(P -> max)*sizeof(char));
    for (int i = 0; i < (P -> max); i++) {
        novaPilha[i] = P -> v[i];
    }
    P -> max = 2*(P -> max);
    free(P -> v);
    P -> v = novaPilha;
}

void Empilha(Pilha P, Palavra palavra) {
    if (P -> topo == P -> max) {
        resize(P);
    }
    P -> v[P -> topo] = palavra;
    (P -> topo)++;    
}

void Desempilha(Pilha P) {
    if (PilhaVazia(P)) {
        return;
    }
    (P -> topo)--;
}

Pilha CriaPilha(int maximo) {
    Pilha P = malloc(sizeof(pilha));
    P -> v = malloc(maximo*sizeof(char));
    P -> topo = 0;
    P -> max = maximo;
    return P;
}

int tamanhoString(char* palavra){
    int percorre, tamanho = 0;
    for (percorre = 0; palavra[percorre] != '\0'; percorre++){
        tamanho++;
    }
    return tamanho;
}

void constroiTamanhos(Palavra* atual){
    // Função similar ao str.len()
    int tamanho = 0, i;
    for(i = 0; atual->texto[i] != '\0'; i++){
        tamanho++;
    }
    atual->tam = tamanho;
}


Livres tamanhosLivresY(int ** matriz, int m, int n){
    // Função que salva os espaços livres na vertical, suas posições e tamanhos.
    Livres tamanhosLivresY;
    tamanhosLivresY.tamanhoVetor = 0;
    tamanhosLivresY.tamanhos = malloc(sizeof(int)*(m*n));
    tamanhosLivresY.posX = malloc(sizeof(int)*(m*n));
    tamanhosLivresY.posY = malloc(sizeof(int)*(m*n));
    int percorre, coluna, linha, contadorTam = 0, posX, posY, i = 0;
    for(coluna = 0; coluna < n; coluna++){
        for (linha = 0; linha < m; linha++){
            contadorTam = 0;
            if(matriz[linha][coluna] == 0){
                posY = linha;
                posX = coluna;
                for(percorre = linha; percorre < m && matriz[percorre][coluna] == 0 ; percorre++){
                    contadorTam++;
                }
            linha = percorre;
            tamanhosLivresY.tamanhos[i] = contadorTam;
            tamanhosLivresY.posX[i] = posX;
            tamanhosLivresY.posY[i] = posY;
            tamanhosLivresY.tamanhoVetor++;
            i++;
            }
        }
    }
    return (tamanhosLivresY);

}

Livres tamanhosLivresX(int ** matriz, int m, int n){
    // Função que salva os espaços livres na horizontal, suas posições e tamanhos.
    Livres tamanhosLivresX;
    tamanhosLivresX.tamanhos = malloc(sizeof(int)*(m*n));
    tamanhosLivresX.posX = malloc(sizeof(int)*(m*n));
    tamanhosLivresX.posY = malloc(sizeof(int)*(m*n));
    tamanhosLivresX.tamanhoVetor = 0;
    int percorre, coluna = 0, linha, contadorTam = 0, posX, posY, i=0;
    for (linha = 0; linha < m; linha++){
        for(coluna = 0; coluna < n; coluna++){
            contadorTam=0;
            if(matriz[linha][coluna] == 0){
                posY = linha;
                posX = coluna;
                for(percorre = coluna; percorre < n && matriz[linha][percorre] == 0; percorre++){
                    contadorTam++;
                }
            coluna = percorre;
            tamanhosLivresX.tamanhos[i] = contadorTam;
            tamanhosLivresX.posX[i] = posX;            
            tamanhosLivresX.posY[i] = posY;
            tamanhosLivresX.tamanhoVetor++;
            i++;
            }
        }
    }
    return (tamanhosLivresX);
}

void imprimeMatriz(char **matrizChar, int m, int n){
    for (int i = 0; i < m; i++){
        for(int j = 0; j<n; j++){
            printf("%c ", matrizChar[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void inserePalavra(char** matrizChar, Palavra* atual, int m, int n, int tentativa, int** matrizInt){
    // Função que insere a palavra na matriz e incrementa em 1 nas respectivas posições da matrizInt
    int linha, coluna, i = 0;
    if (atual-> ori == 0){
        linha = atual->horizontaisY[tentativa];
        for(coluna = atual->horizontaisX[tentativa]; coluna < n && coluna < atual->horizontaisX[tentativa] + atual->tam; coluna++){
            matrizChar[linha][coluna] = atual->texto[i];
            matrizInt[linha][coluna] +=1;
            i++;
        }
        atual->inserida = 1;
    }
    if (atual-> ori == 1){
        coluna = atual->verticaisX[tentativa];
        for(linha = atual->verticaisY[tentativa]; linha < m && linha < atual->verticaisY[tentativa] + atual->tam; linha++){
            matrizChar[linha][coluna] = atual->texto[i];
            matrizInt[linha][coluna] +=1;
            i++;

        }
        atual->inserida = 1;
    }
}

int podeInserir(char** matrizChar, Palavra* atual, int m, int n, int tentativa){
    // Função que verifica se é possível inserir uma palavra em determinada posição da matriz
    int linha, coluna, i = 0;
    if (atual-> ori == 0){
        linha = atual->horizontaisY[tentativa];
        for(coluna = atual->horizontaisX[tentativa]; coluna < n && coluna < atual->horizontaisX[tentativa] + atual->tam; coluna++){
            if (matrizChar[linha][coluna] != '-' && matrizChar[linha][coluna] != atual->texto[i]) return 0;
            i++;
        }
        return 1;
    }
    if (atual-> ori == 1){
        coluna = atual->verticaisX[tentativa];
        for(linha = atual->verticaisY[tentativa]; linha < m && linha < atual->verticaisY[tentativa] + atual->tam; linha++){
            if (matrizChar[linha][coluna] != '-' && matrizChar[linha][coluna] != atual->texto[i]) return 0;
            i++;
        }
        return 1;
    }
    return 1;
}

void possiveisPos(Palavra* atual, Livres espLivre, char** matrizChar, int m, int n){
    // Função que determina as possíveis posições de cada palavra na horizontal e na vertical de acordo com seu tamanho
    int i, j = 0, tamanhoVetor;
    tamanhoVetor = espLivre.tamanhoVetor;
    for(i = 0; i < tamanhoVetor; i++){
        if (atual->ori == 0){
            if (espLivre.tamanhos[i] == atual->tam){
                atual->horizontaisX[j] = espLivre.posX[i];
                atual->horizontaisY[j] = espLivre.posY[i];
                atual->temPossibilidadeH = 1;
                atual->possibilidadesH++;
                j++;
            }
        }
        if (atual->ori == 1){
            if (espLivre.tamanhos[i] == atual->tam){
                atual->verticaisX[j] = espLivre.posX[i];
                atual->verticaisY[j] = espLivre.posY[i];
                atual->temPossibilidadeV = 1;
                atual->possibilidadesV++;
                j++;
            }
        } 
    }
}

void removePalavra(Palavra* atual, char** matrizChar, int m, int n, int** matrizInt){
    // Função que remove a palavra da matriz. A letra de cada palavra só é removida se na mesma posição da matrizInt
    // houver número 1, ou seja, se não for um cruzamento de palavras.
    int linha, coluna;
    if(atual->inserida){
        if (atual-> ori == 0){
            linha = atual->horizontaisY[atual->tentativasH];
            for(coluna = atual->horizontaisX[atual->tentativasH]; coluna < n && coluna < atual->horizontaisX[atual->tentativasH] + atual->tam; coluna++){
                if (matrizInt[linha][coluna] == 1){
                    matrizChar[linha][coluna] = '-';
                }
                matrizInt[linha][coluna] -= 1;
            }
            atual->inserida = 0;
        }

        if (atual-> ori == 1){
            coluna = atual->verticaisX[atual->tentativasV];
            for(linha = atual->verticaisY[atual->tentativasV]; linha < m && linha < atual->verticaisY[atual->tentativasV] + atual->tam; linha++){
                if (matrizInt[linha][coluna] == 1){
                matrizChar[linha][coluna] = '-';
                }
                matrizInt[linha][coluna] -= 1;
            }
            atual->inserida = 0;
        }
    }

}
int procuraSolucao(int m, int n, int** matrizInt, Palavra* palavras, int numPalavras, Livres livresX, Livres livresY, char** matrizChar, int instancia){
    // Função que procura a solução da Palavra-Cruzada
    int i = 0, backtrack, semSol;
    Pilha P = CriaPilha(50*m*n*sizeof(Palavra));
    for(int k = 0; k <numPalavras; k++){
        palavras[k].possibilidadesH = 0;   
        palavras[k].possibilidadesV = 0;
        palavras[k].inserida = 0;
        palavras[k].temPossibilidadeH = 0;
        palavras[k].temPossibilidadeV = 0;
        palavras[k].inserida = 0;
        Palavra* atual = &palavras[k];
        palavras[k].horizontaisX = malloc(sizeof(int)*m*n);
        palavras[k].horizontaisY = malloc(sizeof(int)*m*n);
        palavras[k].verticaisX = malloc(sizeof(int)*m*n);
        palavras[k].verticaisY = malloc(sizeof(int)*m*n);
        constroiTamanhos(atual);
        palavras[k].ori = 0;    
        possiveisPos(atual, livresX, matrizChar, m, n);
        palavras[k].ori = 1;  
        possiveisPos(atual, livresY, matrizChar, m, n);
    }
    while(i < numPalavras){
        semSol = 0;
        Palavra* atual = &palavras[i];
        palavras[i].tentouH = 0;
        palavras[i].tentouV = 0;
        backtrack=0;
        while(atual->tentativasH <= atual->possibilidadesH){
            palavras[i].ori = 0;  
            if (podeInserir(matrizChar, atual, m, n, atual->tentativasH)){
                inserePalavra(matrizChar, atual, m, n, atual->tentativasH, matrizInt);
                Empilha(P, palavras[i]);
                palavras[i].tentouH = 1;
            }
            if(palavras[i].inserida) break;
            if(!(palavras[i].inserida)) atual->tentativasH++;
        }

        while(atual->tentativasV <= atual->possibilidadesV && atual->inserida == 0){
            palavras[i].ori = 1;
            if (podeInserir(matrizChar, atual, m, n, atual->tentativasV)){
                inserePalavra(matrizChar, atual, m, n, atual->tentativasV, matrizInt);
                Empilha(P, palavras[i]);
                palavras[i].tentouV = 1;
            }
            if(palavras[i].inserida) break;
            if(!(palavras[i].inserida)) atual->tentativasV++;
        }

        if(!palavras[i].inserida){ // Backtrack
            if(PilhaVazia(P)){
                semSol = 1;
                printf("Instancia %d\nnao ha solucao\n\n", instancia);
                break;
            }
            else{
            Desempilha(P);
            palavras[i].tentativasH = 0;
            palavras[i].tentativasV = 0;
            i--;
            removePalavra(&(palavras[i]), matrizChar, m, n, matrizInt);
            if(palavras[i].tentouH)
            palavras[i].tentativasH +=1;
            if(palavras[i].tentouV)
            palavras[i].tentativasV +=1;
            backtrack = 1;
            }
        }
        if(!backtrack) i++;
    }
    if(!semSol){
        printf("Instancia %d\n", instancia);
        imprimeMatriz(matrizChar, m, n);
    }
    free(P);
    return 1;
}
